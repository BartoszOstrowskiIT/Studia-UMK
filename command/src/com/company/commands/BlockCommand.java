package com.company.commands;

import com.company.Character;
import com.company.Command;
import com.company.Enemy;

import java.util.Random;

public class BlockCommand implements Command {

    private final Character character;
    private final Enemy enemy;

    public BlockCommand(Character character, Enemy enemy) {
        this.character = character;
        this.enemy = enemy;
    }

    @Override
    public void execute() {
        Random random = new Random();

        int tmp = random.nextInt(26);

        if (tmp < 12) {
            if (!character.isStunned()) {
                enemy.setHealth(enemy.getHealth() - tmp * 2);
                if  (enemy.getHealth() <= 0) {
                    enemy.setHealth(0);
                }
            } else {
                character.setStunned(false);
            }
        } else {
            if (!enemy.isStunned()) {
                character.setHealth(character.getHealth() - tmp);
                if  (character.getHealth() <= 0) {
                    character.setHealth(0);
                }
            } else {
                enemy.setStunned(false);
            }
        }
    }

}
