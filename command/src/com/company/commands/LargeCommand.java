package com.company.commands;

import com.company.Character;
import com.company.Command;

public class LargeCommand implements Command {

    private final Character character;

    public LargeCommand(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        character.setHealth(character.getHealth() + 100);
        character.setLarge(character.getLarge() - 1);
        if  (character.getHealth() >= 100) {
            character.setHealth(100);
        }
    }

}
