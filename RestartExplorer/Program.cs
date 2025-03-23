new KeyChordEventSource(Global.KeyboardAsync(),new(Control,Shift,E)){Enabled=true}.Triggered+=(s,e)=>Start("cmd","/c taskkill /F /IM explorer.exe&&start explorer");
Sleep(MaxValue);