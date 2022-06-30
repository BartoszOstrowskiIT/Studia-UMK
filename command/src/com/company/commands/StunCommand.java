package com.company.commands;

import com.company.Character;
import com.company.Command;
import com.company.Enemy;

import java.util.Random;

public class StunCommand implements Command {

    private final Character character;
    private final Enemy enemy;

    public StunCommand(Character character, Enemy enemy) {
        this.character = character;
        this.enemy = enemy;
    }

    @Override
    public void execute() {
        Random random = new Random();

        int tmp = random.nextInt(100);

        if (tmp >= 60) {
            enemy.setStunned(true);
        } else {
            if (tmp == 0) {
                character.setStunned(true);
            }
            character.setHealth(character.getHealth() - 30);
        }

        if  (character.getHealth() <= 0) {
            character.setHealth(0);
        }
    }

}
