#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define APP_NAME      L"Atom replace-notepad"

#ifdef DEBUG
#define DBG(fmt, ...) { \
  wchar_t _path[MAX_PATH]; \
  GetModuleFileName(NULL, _path, ARRAY_SIZE(_path)); \
  PathRemoveFileSpec(_path); \
  wcscat(_path, L"\\debug.txt"); \
  FILE *_f = _wfopen(_path, L"ab"); \
  fwprintf(_f, TEXT(fmt), ##__VA_ARGS__); \
  fclose(_f); \
}
#else
#define DBG(...)
#endif

int is_elevated() {
  OSVERSIONINFO vi = { sizeof(OSVERSIONINFO) };
  GetVersionEx(&vi);
  if (vi.dwMajorVersion >= 6) { // >= Vista
    HANDLE token;
    TOKEN_ELEVATION elevation;
    DWORD len;
    if (OpenProcessToken(GetCurrentProcess(),TOKEN_READ,&token) && GetTokenInformation(token,TokenElevation,&elevation,sizeof(elevation),&len)) {
      return elevation.TokenIsElevated;
    }
    else {
      return 0;
    }
  }
  return 1;
}

int replace() {
  HKEY key;
  int error = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\notepad.exe", 0, NULL, 0, KEY_SET_VALUE, NULL, &key, NULL);
  if (error != ERROR_SUCCESS) {
    MessageBox(NULL, L"RegCreateKeyEx error: Could not open registry.", APP_NAME, MB_SYSTEMMODAL|MB_ICONWARNING|MB_OK);
    return 1;
  }
  wchar_t path[MAX_PATH], value[MAX_PATH+20];
  GetModuleFileName(NULL, path, ARRAY_SIZE(path));
  swprintf(value, ARRAY_SIZE(value), L"\"%s\" -", path);
  error = RegSetValueEx(key, L"Debugger", 0, REG_SZ, (LPBYTE)value, (wcslen(value)+1)*sizeof(value[0]));
  if (error != ERROR_SUCCESS) {
    MessageBox(NULL, L"RegSetValueEx error: Could not open registry.", APP_NAME, MB_SYSTEMMODAL|MB_ICONWARNING|MB_OK);
    return 2;
  }
  RegCloseKey(key);
  return 0;
}

int restore() {
  int error = RegDeleteKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\notepad.exe", 0, 0);
  if (error != ERROR_SUCCESS) {
    MessageBox(NULL, L"RegDeleteKeyEx error: Could not open registry.\n\nNotepad is probably not replaced.", APP_NAME, MB_SYSTEMMODAL|MB_ICONWARNING|MB_OK);
    return 1;
  }
  return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  DBG("lpCmdLine: %s\n", lpCmdLine);

  if (!is_elevated() && (!wcscmp(lpCmdLine,L"replace") || !wcscmp(lpCmdLine,L"restore"))) {
    int opt = MessageBox(NULL, L"Depending on your UAC settings, you may get a prompt to run replace-notepad.exe with administrator privileges. This is needed to setup the Notepad.exe redirection.\n\nNote that this will affect all users on this machine, so if there are multiple users on your machine, be sure to read the caveats in the package README first.\n\nContinue?", APP_NAME, MB_SYSTEMMODAL|MB_ICONINFORMATION|MB_YESNO);
    if (opt == IDNO) {
      return 1;
    }
    wchar_t path[MAX_PATH];
    GetModuleFileName(NULL, path, ARRAY_SIZE(path));
    int ret = (INT_PTR) ShellExecute(NULL, L"runas", path, lpCmdLine, NULL, SW_SHOWNORMAL);
    if (ret > 32) {
      return 0; // success
    }
    else {
      MessageBox(NULL, L"Could not redirect Notepad.exe.", APP_NAME, MB_SYSTEMMODAL|MB_ICONERROR|MB_OK);
    }
    return 1;
  }

  if (!wcscmp(lpCmdLine,L"replace")) {
    if (replace() == 0) {
      MessageBox(NULL, L"Successfully replaced Notepad.", APP_NAME, MB_SYSTEMMODAL|MB_ICONINFORMATION|MB_OK);
    }
    else {
      MessageBox(NULL, L"Error replacing Notepad.", APP_NAME, MB_SYSTEMMODAL|MB_ICONERROR|MB_OK);
    }
    return 0;
  }

  if (!wcscmp(lpCmdLine,L"restore")) {
    if (restore() == 0) {
      MessageBox(NULL, L"Successfully restored Notepad.", APP_NAME, MB_SYSTEMMODAL|MB_ICONINFORMATION|MB_OK);
    }
    else {
      MessageBox(NULL, L"Error restoring Notepad.", APP_NAME, MB_SYSTEMMODAL|MB_ICONERROR|MB_OK);
    }
    return 0;
  }

  // Get path to atom.cmd
  wchar_t path[MAX_PATH];
  GetEnvironmentVariable(L"LOCALAPPDATA", path, ARRAY_SIZE(path));
  // DBG("LOCALAPPDATA: %s\n", path);
  wcscat(path, L"\\atom\\bin\\atom.cmd");

  if (!PathFileExists(path)) {
    // Can't find atom.cmd. This can easily happen on a multi-user machine.
    int opt = MessageBox(NULL, L"Could not find atom.cmd. Do you want to restore Notepad?", APP_NAME, MB_ICONERROR|MB_YESNO);
    if (opt == IDYES) {
      GetModuleFileName(NULL, path, ARRAY_SIZE(path));
      ShellExecute(NULL, L"runas", path, L"restore", NULL, SW_SHOWNORMAL);
    }
    return 1;
  }

  if (lpCmdLine[0] == '\0') {
    MessageBox(NULL, L"No arguments were passed. Don't know what to do.", APP_NAME, MB_ICONWARNING|MB_OK);
    return 0;
  }

  wchar_t *dash = wcsstr(lpCmdLine, L"- ");
  if (dash == NULL) {
    MessageBox(NULL, L"Error parsing lpCmdLine.", APP_NAME, MB_ICONERROR|MB_OK);
    return 0;
  }

  // Copy any arguments that may be specified before the dash
  dash[0] = '\0';
  wchar_t args[MAX_PATH] = L"";
  wcscpy(args, lpCmdLine);

  // Skip "C:\WINDOWS\system32\NOTEPAD.EXE"
  wchar_t *start = dash+2;
  while (*start != '\0') {
    if (*start == ' ') {
      start++;
      break;
    }
    start++;
  }

  // Copy the target file to the arguments
  if (*start == '"') {
    wcscat(args, start);
  }
  else {
    wcscat(args, L"\"");
    wcscat(args, start);
    wcscat(args, L"\"");
  }

  // DBG("Launching: %s %s\n", path, args);
  ShellExecute(NULL, NULL, path, args, NULL, SW_HIDE);
  return 0;
}
