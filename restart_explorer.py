import keyboard    #для хоткея
import subprocess  #для создания кмд 

def restart_explorer():
    """"""""""
    создается кмд и перезапускает экплорер
    """""""""
    subprocess.run(["taskkill", "/f", "/im", "explorer.exe"]) 
    subprocess.Popen(["explorer.exe"])

# Назначаем хоткей ctrl+shift+e и выполняем функцию
keyboard.add_hotkey('ctrl+shift+e', restart_explorer)  

# Держать скрипт включеннным
while True:
    pass