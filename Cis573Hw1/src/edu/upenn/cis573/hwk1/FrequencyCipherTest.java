package edu.upenn.cis573.hwk1;

import static org.junit.Assert.*;

import java.io.File;

import org.junit.Test;

public class FrequencyCipherTest {

	@Test
	public void testEncrpytion() {
		Main testCipher = new Main();
		testCipher.shiftValue = 1;
		File toEncrypt = new File("src/testEncrypt.txt");
		String encryptedString = testCipher.encrypt(toEncrypt);
		assertEquals("Encryption not successful", "ijjbnbtuvefoupgqfoo", encryptedString);
	}
	
	@Test
	public void testFile2String() {
		Main testCipher = new Main();
		File toRead = new File("src/testEncrypt.txt");
		String stringRead = testCipher.fileToStr(toRead);
		assertEquals("Hi! I am a student of Penn;\n", stringRead);
	}
}
