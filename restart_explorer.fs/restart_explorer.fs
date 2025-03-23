open System
open System.Diagnostics
open System.Security.Principal
open WindowsInput.Events
open WindowsInput.Events.Sources
open Fli

let program () =
    
    use identity = WindowsIdentity.GetCurrent()
    let principal = new WindowsPrincipal(identity);
    printfn (match principal.IsInRole(WindowsBuiltInRole.Administrator) with
            | true -> "admin"
            | false -> "not admin")
    
    printfn "started"
    use keyboard = WindowsInput.Capture.Global.KeyboardAsync()
    
    use listener =
        new KeyChordEventSource(keyboard, new ChordClick(KeyCode.Control, KeyCode.Shift, KeyCode.E))
    
    let handler =
        new EventHandler<KeyChordEventArgs>(fun e ->
            printfn "ok"
            
            cli {
                Shell CMD
                Command "taskkill /f /im explorer.exe"
            }
            |> Command.execute |> ignore            
            printfn "explorer is killed"
            
            Async.Sleep 100 |> Async.RunSynchronously
            use process_ = Process.Start("explorer.exe")
            printfn "explorer started"
            
            ignore)

    listener.Triggered.AddHandler(handler)

    listener.Reset_On_Parent_EnabledChanged <- false
    listener.Enabled <- true

    printfn "Input enter to exit."
    Console.ReadLine() |> ignore

program ()
printfn "ended"