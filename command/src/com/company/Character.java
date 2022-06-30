package com.company;

public class Character {

    private int health;

    private int small;
    private int medium;
    private int large;

    private boolean stunned;

    public Character() {
        setHealth(100);
        setStunned(false);
        setSmall(1);
        setMedium(0);
        setLarge(0);
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

    public int getSmall() {
        return small;
    }

    public void setSmall(int small) {
        this.small = small;
    }

    public int getMedium() {
        return medium;
    }

    public void setMedium(int medium) {
        this.medium = medium;
    }

    public int getLarge() {
        return large;
    }

    public void setLarge(int large) {
        this.large = large;
    }

    @Override
    public String toString() {
        return "Character health: " + health + (isStunned() ? " stunned" : "");
    }
}
