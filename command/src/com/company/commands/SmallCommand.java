package com.company.commands;

import com.company.Character;
import com.company.Command;

import java.util.Random;

public class SmallCommand implements Command {

    private final Character character;

    public SmallCommand(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        character.setHealth(character.getHealth() + 25);
        character.setSmall(character.getSmall() - 1);
        if  (character.getHealth() >= 100) {
            character.setHealth(100);
        }
    }

}
