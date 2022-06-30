package com.company.commands;

import com.company.Character;
import com.company.Command;
import com.company.Enemy;

import java.util.Random;

public class AttackCommand implements Command {
    private final Character character;
    private final Enemy enemy;

    public AttackCommand(Character character, Enemy enemy) {
        this.character = character;
        this.enemy = enemy;
    }

    @Override
    public void execute() {
        Random random = new Random();

        if (!character.isStunned()) {
            enemy.setHealth(enemy.getHealth() - random.nextInt(51));
            if  (enemy.getHealth() <= 0) {
                enemy.setHealth(0);
            }
        } else {
            character.setStunned(false);
        }

        if (!enemy.isStunned()) {
            character.setHealth(character.getHealth() - random.nextInt(26));
            if  (character.getHealth() <= 0) {
                character.setHealth(0);
            }
        } else {
            enemy.setStunned(false);
        }
    }

}
