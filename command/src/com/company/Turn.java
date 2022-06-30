package com.company;

import java.util.HashMap;

public class Turn {
    private final HashMap<String, Command> commandMap = new HashMap<>();

    public void register(String commandName, Command command) {
        commandMap.put(commandName, command);
    }

    public boolean execute(String commandName) {
        Command command = commandMap.get(commandName);
        if (command == null) {
            return false;
        }
        command.execute();
        return true;
    }

    public Turn() {
    }

    public HashMap<String, Command> getCommandMap() {
        return commandMap;
    }
}
