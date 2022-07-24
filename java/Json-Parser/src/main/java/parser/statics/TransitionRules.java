package parser.statics;

public class TransitionRules {
	private static boolean continueJson = false; 
	
	private static boolean continueArray = false;
	
	private static boolean isTrueTrans = true;
	
	private static boolean isSubJson = false;
	
	private static boolean isSubArray = false;
	
	public static boolean getIsSubJson() {
		return isSubJson;
	}
	
	public static void setIsSubJson(boolean flag) {
		isSubJson = flag;
	}
	
	public static boolean getIsSubArray(boolean flag) {
		return isSubArray;
	}
	
	public static void setIsSubArray(boolean flag) {
		isSubArray = flag;
	}
	
	public static void setBoolRule(boolean flag) {
		isTrueTrans = flag;
	}
	public static boolean getBoolRule() {
		return isTrueTrans;
	}
	
	public static void setJsonRule(boolean flag) {
		continueJson = flag;
	}
	
	public static void setArrayRule(boolean flag) {
		continueArray = flag;
	}
	
	public static boolean checkJsonRule() {
		return continueJson;
	}
	
	public static boolean checkArrayRule() {
		return continueArray;
	}
	
}
