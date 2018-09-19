//package Satori;

import java.io.IOException;
import java.nio.CharBuffer;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public final class Agent implements TajnyAgent, Readable {

    final HashMap<String, Character> morseToChar = new HashMap<String, Character>() {
        {
            put(".-", 'a');
            put("-...", 'b');
            put("-.-.", 'c');
            put("-..", 'd');
            put(".", 'e');
            put("..-.", 'f');
            put("--.", 'g');
            put("....", 'h');
            put("..", 'i');
            put(".---", 'j');
            put("-.-", 'k');
            put(".-..", 'l');
            put("--", 'm');
            put("-.", 'n');
            put("---", 'o');
            put(".--.", 'p');
            put("--.-", 'q');
            put(".-.", 'r');
            put("...", 's');
            put("-", 't');
            put("..-", 'u');
            put("...-", 'v');
            put(".--", 'w');
            put("-..-", 'x');
            put("-.--", 'y');
            put("--..", 'z');
            put(".-.-", 'ą');
            put("-.-..", 'ć');
            put("..-..", 'ę');
            put(".-..-", 'ł');
            put("--.--", 'ń');
            put("---.", 'ó');
            put("...-...", 'ś');
            put("--..-.", 'ź');
            put("--..-", 'ż');
            put(".-.-.-", '.');
            put("--..--", ',');
            put(".----.", '\'');
            put(".-..-.", '"');
            put("..--.-", '_');
            put("---...", ':');
            put("-.-.-.", ';');
            put("..--..", '?');
            put("-.-.--", '!');
            put("-....-", '-');
            put(".-.-.", '+');
            put("-..-.", '/');
            put("-.--.", '(');
            put("-.--.-", ')');
            put("-...-", '=');
            put(".--.-.", '@');
            
            put("-----", '0');
            put(".----", '1');
            put("..---", '2');
            put("...--", '3');
            put("....-", '4');
            put(".....", '5');
            put("-....", '6');
            put("--...", '7');
            put("---..", '8');
            put("----.", '9');
            
            


        }
    };

    final HashMap<Character, String> charToMorse = new HashMap<Character, String>();
    {
        for (Map.Entry<String, Character> k : morseToChar.entrySet()) {
            charToMorse.put(k.getValue(), k.getKey());
        }
    }

    TajnyAgent listeningToAgent = null;
    String transmittingMessage = "pawiany/wchodzą/na/ściany!żyrafy/wchodzą/do/szafy!";
    private int currentLetterIndex = 0;
    private int currentMorseIndex = 0;
    boolean defaultMessage = true;
    boolean nextWordIsZuber = false;

    public Agent() {
    }

    public Agent(String message) {
        transmittingMessage = message;
        defaultMessage = false;
    }

    public Agent(TajnyAgent agent) {
        listeningToAgent = agent;
    }

    public Agent(TajnyAgent agent, String message) {
        transmittingMessage = message;
        listeningToAgent = agent;
        defaultMessage = false;
    }

    public boolean isPunctuation(char letter) {
        return (letter == '.' || letter == ',' || letter == '\'' || letter == '"' || letter == '_' || letter == ':'
                || letter == ';' || letter == '?' || letter == '!' || letter == '-' || letter == '+' || letter == '/'
                || letter == '(' || letter == ')' || letter == '=' || letter == '@');
    }

    @Override
    public int read(CharBuffer cb) throws IOException {
        //        while (true) {
        //            try {
        //                listeningToAgent.transmituj();
        //            } catch (Stop e) {
        //
        //            } catch (Koniec e) {
        //                break;
        //            } catch (RuntimeException e) {
        //
        //            }
        //        }

        String currentMorse = "";
        int numberOfLetters = 0;
        while (true) {
            try {
                listeningToAgent.transmituj();
                currentMorse += '-';
            } catch (Stop e) {
                char letter = morseToChar.get(currentMorse);
                numberOfLetters++;
                cb.append(letter);
                currentMorse = "";
                if (isPunctuation(letter)) {
                    return numberOfLetters;
                }
            } catch (Koniec e) {
                return -1;
            } catch (RozmowaKontrolowana e) {

            } catch (Zuber e) {
                for (int x = currentLetterIndex; x <= transmittingMessage.length(); x++) {
                    if (x == 0 || x == transmittingMessage.length()
                            || isPunctuation(transmittingMessage.charAt(x - 1))) {
                        transmittingMessage = transmittingMessage.substring(0, x) + "zuber/"
                                + transmittingMessage.substring(x, transmittingMessage.length());
                        break;
                    }
                }

            } catch (RuntimeException e) {
                currentMorse += '.';
            }
        }
    }

    @Override
    public void transmituj() {
        if (currentLetterIndex == transmittingMessage.length()) {
            currentMorseIndex = 0;
            currentLetterIndex = 0;
            if (!defaultMessage)
                throw new Koniec();
        }

        String morse = charToMorse.get(transmittingMessage.charAt(currentLetterIndex));
        if (currentLetterIndex < transmittingMessage.length() && currentMorseIndex == morse.length()) {
            currentLetterIndex++;
            currentMorseIndex = 0;
            throw new Stop();
        }

        if (morse.charAt(currentMorseIndex) == '-') {
            currentMorseIndex++;
            return;
        } else {
            currentMorseIndex++;
            throw new RuntimeException();
        }
    }

}