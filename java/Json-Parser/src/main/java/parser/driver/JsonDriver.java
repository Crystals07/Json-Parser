package parser.driver;

import java.io.File;
import parser.constants.ConstantsNumbers;
import parser.constants.JsonConstants;
import parser.utils.ParserUtils;

public class JsonDriver {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		if(validArgs(args)) {
			
			String json = ParserUtils.getJson(args,JsonConstants.YES_FLAG.equalsIgnoreCase(args[0]));
			boolean debugflag = getDebugFlag(ConstantsNumbers.NUM_TWO.equals(args.length)?args[1]:args[2]);
			
			System.out.println(json);
			JsonParser jp = new JsonParser();
			System.out.println(jp.parse(json,debugflag)?"Json Valid":"Json Invalid");
		}		
		
	}
	
	private static boolean getDebugFlag(String flag) {
		return (JsonConstants.YES_FLAG.equals(flag)?true:false);
	}

	public static boolean validArgs(String[] args) {
				
		if(args.length<2||args.length>3||(JsonConstants.NO_FLAG.equalsIgnoreCase(args[0])&&args.length>2)){
			System.out.println("Invalid No of Arguments : "+ args.length);
			return false;
		}		
		else {
			if(ConstantsNumbers.NUM_THREE.equals(args.length)) {
				return (isFlagValid(args[0]) && isPathValid(args[1]) && isFlagValid(args[2]));
			}		
			else {
				return (isFlagValid(args[0]) && isFlagValid(args[1]));
			}
		}
	}
	
	private static boolean isFlagValid(String flag) {
		if(!(JsonConstants.YES_FLAG.equalsIgnoreCase(flag)||JsonConstants.NO_FLAG.equalsIgnoreCase(flag))) {
			System.out.println("Invalid Falg it should be Y or N");
			return false;
		}
		return true;
	}

	public static boolean isPathValid(String path) {
		
		try {
				File file = new File(path);
				if(file.isDirectory()) {
					System.out.println("Specify File not Directory");
					return false;
				}
				else if(!file.exists()) {
					System.out.println("File path does not exists");
					return false;
				}
				
		} catch(Exception e) {
				System.out.println("File path is invalid "+e.getMessage());
				return false;
		}		
		return true;
	}
}
