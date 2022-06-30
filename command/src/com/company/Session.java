package com.company;

import com.company.commands.*;

import java.util.Random;

public class Session {

    private Turn turn;

    private boolean end = false;
    private boolean battle = true;

    private int score = 0;

    private Character character;
    private Enemy enemy;

    public Session() {
        setTurn(new Turn());
        setCharacter(new Character());
        setEnemy(new Enemy());

        Command attack = new AttackCommand(getCharacter(), getEnemy());
        getTurn().register("attack", attack);

        Command block = new BlockCommand(getCharacter(), getEnemy());
        getTurn().register("block", block);

        Command stun = new StunCommand(getCharacter(), getEnemy());
        getTurn().register("stun", stun);
    }

    public Turn getTurn() {
        return turn;
    }

    private void setTurn(Turn turn) {
        this.turn = turn;
    }

    public boolean isEnd() {
        return end;
    }

    public void setEnd(boolean end) {
        this.end = end;
    }

    public boolean isBattle() {
        return battle;
    }

    public void setBattle(boolean battle) {
        this.battle = battle;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public Character getCharacter() {
        return character;
    }

    public void setCharacter(Character character) {
        this.character = character;
    }

    public Enemy getEnemy() {
        return enemy;
    }

    public void setEnemy(Enemy enemy) {
        this.enemy = enemy;
    }

    public void nextTurn() {
        Random random = new Random();

        setTurn(new Turn());

        if (getEnemy().getHealth() == 0) {
            if (isBattle()) {
                score++;
            }
            setBattle(false);
            if (random.nextBoolean()) {
                enemy = new Enemy();
                setBattle(true);
            }
        }

        if (getCharacter().getHealth() == 0 || score == 100) {
            setEnd(true);
        }

        if (isBattle()) {
            Command attack = new AttackCommand(getCharacter(), getEnemy());
            getTurn().register("attack", attack);

            Command block = new BlockCommand(getCharacter(), getEnemy());
            getTurn().register("block", block);

            Command stun = new StunCommand(getCharacter(), getEnemy());
            getTurn().register("stun", stun);

            if (character.getSmall() > 0) {
                Command small = new SmallCommand(getCharacter());
                getTurn().register("small", small);
            }

            if (character.getMedium() > 0) {
                Command medium = new MediumCommand(getCharacter());
                getTurn().register("medium", medium);
            }

            if (character.getLarge() > 0) {
                Command large = new LargeCommand(getCharacter());
                getTurn().register("large", large);
            }

        } else {
            Command rest = new RestCommand(getCharacter());
            getTurn().register("rest", rest);

            Command craft = new CraftCommand(getCharacter());
            getTurn().register("craft", craft);
        }
    }
}
