package com.company;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            Session session = new Session();
            Turn turn = session.getTurn();
            System.out.println("New game");
            System.out.println("Defeat 100 enemies to escape the labyrinth");

            System.out.println(session.getCharacter());
            System.out.println(session.getEnemy());
            System.out.println(turn.getCommandMap().keySet());

            String line;
            while (true) {
                if ((line = reader.readLine()) != null) {
                    System.out.println();
                    if (line.equalsIgnoreCase("exit")) {
                        break;
                    } else {
                        turn = session.getTurn();

                        if (turn.execute(line)) {
                            session.nextTurn();
                            turn = session.getTurn();
                        } else {
                            System.out.println("Command not found");
                        }

                        if (session.isEnd()) {
                            if (session.getScore() == 100) {
                                System.out.println("You win");
                                System.out.println("Score: " + session.getScore() +  "/100");
                            } else {
                                System.out.println("You lose");
                                System.out.println("Score: " + session.getScore() +  "/100");
                            }
                            break;
                        }

                        System.out.println(session.getCharacter());
                        if (session.isBattle()) {
                            System.out.println(session.getEnemy());
                        }
                        System.out.println(turn.getCommandMap().keySet());
                    }
                }
            }

            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
