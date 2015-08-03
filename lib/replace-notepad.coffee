{CompositeDisposable} = require 'atom'
spawn = require('child_process').spawn

module.exports = ReplaceNotepad =
  subscriptions: null

  activate: (state) ->
    @subscriptions = new CompositeDisposable
    @subscriptions.add atom.commands.add 'atom-workspace', 'replace-notepad:replace': => @replace()
    @subscriptions.add atom.commands.add 'atom-workspace', 'replace-notepad:restore': => @restore()

  deactivate: ->
    @subscriptions.dispose()

  replace: ->
    spawn "#{process.env.USERPROFILE}\\.atom\\packages\\replace-notepad\\bin\\replace-notepad.exe", ["replace"]

  restore: ->
    spawn "#{process.env.USERPROFILE}\\.atom\\packages\\replace-notepad\\bin\\replace-notepad.exe", ["restore"]
