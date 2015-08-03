{CompositeDisposable} = require 'atom'
child_process = require 'child_process'

module.exports = ReplaceNotepad =
  subscriptions: null

  activate: (state) ->
    @subscriptions = new CompositeDisposable
    @subscriptions.add atom.commands.add 'atom-workspace', 'replace-notepad:replace': => @replace()
    @subscriptions.add atom.commands.add 'atom-workspace', 'replace-notepad:restore': => @restore()

  deactivate: ->
    @subscriptions.dispose()

  replace: ->
    child_process.spawn "#{process.env.USERPROFILE}\\.atom\\packages\\replace-notepad\\bin\\replace-notepad.exe", ["replace"]

  restore: ->
    child_process.spawn "#{process.env.USERPROFILE}\\.atom\\packages\\replace-notepad\\bin\\replace-notepad.exe", ["restore"]
