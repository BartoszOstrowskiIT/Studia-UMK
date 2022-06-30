package com.company.commands;

import com.company.Character;
import com.company.Command;

import java.util.Random;

public class RestCommand implements Command {

    private final Character character;

    public RestCommand(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        Random random = new Random();

        character.setHealth(character.getHealth() + random.nextInt(26));
        if  (character.getHealth() >= 100) {
            character.setHealth(100);
        }
    }

}
