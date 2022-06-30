package com.company.commands;

import com.company.Character;
import com.company.Command;

import java.util.Random;

public class CraftCommand implements Command {

    private final Character character;

    public CraftCommand(Character character) {
        this.character = character;
    }

    @Override
    public void execute() {
        Random random = new Random();

        int tmp = random.nextInt(4);

        switch (tmp) {
            case 0:
                System.out.println("fail");
                System.out.println();
                break;
            case 1:
                System.out.println("small potion");
                System.out.println();
                character.setSmall(character.getSmall() + 1);
                break;
            case 2:
                System.out.println("medium potion");
                System.out.println();
                character.setMedium(character.getMedium() + 1);
                break;
            case 3:
                System.out.println("large potion");
                System.out.println();
                character.setLarge(character.getLarge() + 1);
                break;
        }
    }

}
