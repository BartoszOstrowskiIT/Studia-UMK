package com.company.commands;

import com.company.Character;
import com.company.Command;

public class MediumCommand implements Command {

    private final Character character;

    public MediumCommand(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        character.setHealth(character.getHealth() + 50);
        character.setMedium(character.getMedium() - 1);
        if  (character.getHealth() >= 100) {
            character.setHealth(100);
        }
    }

}
