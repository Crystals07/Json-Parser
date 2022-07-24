package parser.utils;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import parser.constants.JsonConstants;

public class ParserUtils {
	
	public static String getJson(String[] args,boolean flag) {
		
		BufferedReader bfread; 
		if(flag) {
			try {
				bfread = new BufferedReader(new FileReader(args[1]));
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("File not found !");
				return null;
			}
		}
		
		else {
			System.out.println("Enter the json add ! to quit");
			bfread = new BufferedReader(new InputStreamReader(System.in));
		}
		
		StringBuilder temp = new StringBuilder();
		String line = new String();
		try {
			while((line = bfread.readLine())!=null && !JsonConstants.TERMINATE_INPUT.equals(line)) {  
					temp.append(line).append(JsonConstants.NEW_LINE);
			}
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}	
		
		try {
				bfread.close();
		} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
		}
		
		return temp.toString();
	}

	public static boolean isInt(String currentChar,boolean firstNum) {
		if(firstNum) {
			if(JsonConstants.NEGATIVE_CHAR.equals(currentChar)) return true;
		}
		
		try {
			
			Integer.parseInt(currentChar);
			
		} catch(Exception e) {
			
			return false;
		}
		
		return true;
	}
}
