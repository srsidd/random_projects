package edu.upenn.cis573.hwk1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.Map.Entry;


public class Main {

	public static int shiftValue;
	public static float totalCorrect = 0;
	public static float totalIncorrect = 0;

	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);

		// Get the folder from which the text files are to be read
		String path = new File(args[0]).getAbsolutePath();
		File folder = new File(path);
		
		// Check if path of the folder is valid
		if(!folder.isDirectory()) {
			System.out.println("Invalid path, Exiting program");
			System.exit(0);
		}
		
		// Check if the folder is empty
		if(folder.list().length<1) {
			System.out.println("Empty directory, Exiting program");
			System.exit(0);
		}
		
		if(!folder.canRead()) {
			System.out.println("Folder cannot be read, Exiting program");
			System.exit(0);
		}
		
		// Check if number of arguments is 1
		if(args.length != 1)
	    {
	        System.out.println("Invalid number of arguments, Exiting program");
	        System.exit(0);
	    }

		shiftValue = 2;
		//		File folder = new File("/home/siddharth/Documents/Upenn/CIS573/homework1/corpus/");

		String encrypted = new String();
		String decrypted = new String();

		Map<Character, Integer> letterFreq = new TreeMap<Character, Integer>();
		File[] listOfFiles = folder.listFiles();

		// Iterate through each file within the corpus
		for (File CurFile : listOfFiles) {
			if (CurFile.isFile()) {
				Map<Character, Integer> freqModelInv = new TreeMap<Character, Integer>();
				Map<Integer, Character> freqModel = new TreeMap<Integer, Character>();

				// Encrypt each file from the corpus
				encrypted = encrypt(CurFile);

				// Perform Leave one out cross validation to avoid over fitting
				for (File NextFile : listOfFiles) {

					// Build a frequency model from all files excepted the encrypted file
					if (NextFile != CurFile) {
						letterFreq = formModel(NextFile);

						// Add the frequency count of the current file to the model
						for(Entry<Character, Integer> entry : letterFreq.entrySet()) {
							if (freqModelInv.get(entry.getKey()) == null) {
								freqModelInv.put(entry.getKey(), entry.getValue());
							}
							else {
								freqModelInv.put(entry.getKey(),freqModelInv.get(entry.getKey()) + entry.getValue());
							}
						}
					}
				}

				// Invert the map to get the alphabet as the value and the count as the key
				for(Entry<Character, Integer> entry: freqModelInv.entrySet()) {
					freqModel.put(entry.getValue(), entry.getKey());
				}

				// Decrpyt the file based on the model
				decrypted = decrypt(encrypted, freqModel);

				// Accumulate accuracy of each document
				getError(CurFile, decrypted);
				//System.out.println("time = " + System.nanoTime());
			}
			else {
				System.out.println("Invalid File");
			}
		}
		input.close();


		System.out.print("totalCorrect = " + totalCorrect);
		System.out.println("    totalIncorrect = " + totalIncorrect);
		System.out.println("Overall Accuracy of the Corpus = " + (totalCorrect/ (float)totalIncorrect)*100);
	}

	public static String encrypt(File toEncrypt) { 
		// Function to perform simple substitution cipher.
		String content;
		//		try {
		content = fileToStr(toEncrypt);
		String enc = new String();
		int value;
		int counter = 0;
		List<Integer> asc = new ArrayList<Integer>();

		// Loop through all the characters in the file and add an offset to the ASCII character
		for (int i=0; i<content.length(); i++) {
			char c = content.charAt(i);
			if (Character.isLetter(c)) {
				if (Character.isUpperCase(c)) {
					c = Character.toLowerCase(c);
				}
				asc.add((int)c + shiftValue);
				value = asc.get(counter);
				counter++;
				enc = enc + Character.toString((char) value);
			}
		}
		System.out.println("Encoded file = " + toEncrypt);
		return enc;
		//		} catch (IOException e) {
		//			System.out.println("Invalid IO - Is the file correct?");
		//			return "";
		//		}
	}

	public static Map<Character, Integer> formModel(File toModel) {
		String content;
		Map<Character, Integer> rank = new TreeMap<Character, Integer>();
		//		try {
		content = fileToStr(toModel);

		// Loop through all the characters in the file and add an offset to the ASCII character		
		for (int i=0; i<content.length(); i++) {
			char c = content.charAt(i);
			if (Character.isLetter(c)) {
				if (Character.isUpperCase(c)) {
					c = Character.toLowerCase(c);
				}
				if (rank.get(c) == null) {
					rank.put(c, 1);
				}
				else {
					rank.put(c, rank.get(c)+1);
				}
			}
		}
		return rank;
		//		} catch (IOException e) {
		//			System.out.println("Invalid IO - Is the file correct?");
		//			return rank;
		//		}
	}

	public static String decrypt(String toDecrypt, Map<Integer, Character> model) { 
		Map<Character, Integer> rank = new TreeMap<Character, Integer>();
		Map<Integer, Character> count = new TreeMap<Integer, Character>();
		Map<Character, Character> table = new TreeMap<Character, Character>();

		ArrayList<Character> tableKey = new ArrayList<Character>();
		ArrayList<Character> tableValue = new ArrayList<Character>();

		String decrypted = "";
		// Loop through all the characters in the file and add an offset to the ASCII character		
		for (int i=0; i<toDecrypt.length(); i++) {
			char c = toDecrypt.charAt(i);
			if (Character.isUpperCase(c)) {
				c = Character.toLowerCase(c);
			}
			if (rank.get(c) == null) {
				rank.put(c, 1);
			}
			else {
				rank.put(c, rank.get(c)+1);
			}
		}
		for(Entry<Character, Integer> entry: rank.entrySet()) {
			count.put(entry.getValue(), entry.getKey());
		}
		//		System.out.println("decoded freq count = " + count);

		for(int k:count.keySet()) {
			tableKey.add(count.get(k));
		}

		for(int k:model.keySet()) {
			tableValue.add(model.get(k));
		}
		for(int i = 0; i < tableValue.size(); i++) {
			table.put(tableKey.get(i), tableValue.get(i));
		}
		//		System.out.println("comparison table = " + table);

		// Use the comparison table to decrypt the file
		for (int i=0; i<toDecrypt.length(); i++) {
			char c = toDecrypt.charAt(i);
			if (Character.isUpperCase(c)) {
				c = Character.toLowerCase(c);
			}
			decrypted = decrypted + Character.toString(table.get(c));
		}

		return decrypted;
	}

	private static void getError(File originalFile, String decrypted) {
		int sameChar = 0;
		String original;
		//		try {
		original = fileToStr(originalFile);
		String toCompare = "";

		for (int i=0; i<original.length(); i++) {
			char c = original.charAt(i);
			if (Character.isLetter(c)) {
				if (Character.isUpperCase(c)) {
					c = Character.toLowerCase(c);
				}
				toCompare = toCompare + c;
			}
		}

		for (int i = 0; i < decrypted.length(); i++) {
			if (toCompare.charAt(i) == decrypted.charAt(i)) {
				sameChar++;
			}
		}

		totalCorrect = totalCorrect + (float)sameChar;
		totalIncorrect = totalIncorrect + (float)decrypted.length();
		System.out.print("Correctly Decoded = " + sameChar);
		System.out.print("    Uncorrectly Decoded = " + (decrypted.length() - sameChar));
		System.out.println("    Accuarcy = " + (sameChar /(float)decrypted.length())*100);
		System.out.println();
	}

	public static String fileToStr(File readFile) {
		BufferedReader br;
		try {
			br = new BufferedReader(new FileReader(readFile));
			StringBuilder sb = new StringBuilder();
			String line;
			try {
				line = br.readLine();
				while (line != null) {
					sb.append(line);
					sb.append(System.lineSeparator());
					line = br.readLine();
				}
				String everything = sb.toString();
				br.close();
				return everything;
			} catch (IOException e) {
				System.out.println("Invalid IO - Is the file correct?");
				return "";
			}

		} catch (FileNotFoundException e) {
			System.out.println("Invalid IO - Is the file correct?");
			return "";
		}
	}
}
