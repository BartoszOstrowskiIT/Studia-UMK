package com.company;

public class Enemy {

    private int health;

    private boolean stunned;

    public Enemy() {
        setHealth(100);
        setStunned(false);
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public boolean isStunned() {
        return stunned;
    }

    public void setStunned(boolean stunned) {
        this.stunned = stunned;
    }

    @Override
    public String toString() {
        return "Enemy health: " + health + (isStunned() ? " stunned" : "");
    }
}
