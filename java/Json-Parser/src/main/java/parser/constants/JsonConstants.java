package parser.constants;

import com.google.common.collect.ImmutableList;

import parser.states.State;
import parser.states.common.StartState;

//import java.util.regex;
import java.util.regex.Pattern;

public class JsonConstants {
	
	public static final ImmutableList<String> E_LIST = ImmutableList.of(" ","\t");
	
	public static final ImmutableList<String> S_LIST = ImmutableList.of("*","#","%","&","$","!");
	
	public static final ImmutableList<String> E_NEW_LINE= ImmutableList.of(" ","\n","\t");
	
	public static final ImmutableList<String> VALID_NUM = ImmutableList.of();
	
	public static final String NEGATIVE_CHAR = "-";
	
	public static final Integer ERROR_SEGMENT_DEFAULT = 10; 
	
	public static final ImmutableList<String> SPACE_TAB = ImmutableList.of(" ","\t");
	
	public static final String ESC_CHR = "\\";
	
	public static final String JSON_START = "{";
	
	public static final String JSON_END = "}";
	
	public static final String JSON_ARRAY_START = "[";
	
	public static final String JSON_ARRAY_END = "]";
	
	public static final String LAST_STATE = "L";
	
	public static final String FINAL_STATE = "F";
	
	//public static final String CHAR_D = "D";
	
	public static final String YES_FLAG = "Y";
	
	public static final String NO_FLAG = "N";
	
	public static final String QUOTES = "\"";
	
	public static final String TERMINATE_INPUT = "!";
	
	public static final String NEW_LINE = "\n";

	public static final String JSON_START_OF_KEY = " Start of Json Key ";
	
	public static final String JSON_START_OF_STRING_VALUE = " Start of Json String Value ";

	public static final String JSON_MID_OF_KEY = " Mid of Json Key ";

	public static final String JSON_END_OF_KEY = " End of Json Key ";
	
	public static final String JSON_END_OF_STRING_VALUE = " End of Json Key ";

	public static final String JSON_START_OF_KEY_VALUE_SEP = " Start of Key Value Seperator ";

	public static final String COLON = ":";

	public static final String JSON_AT_KEY_VALUE_SEP = " At Key Value Seperator ";

	public static final String JSON_AT_END_KEY_VALUE_SEP = " At End of Key Value Seperator ";

	public static final String CHAR_T = "t";

	public static final String CHAR_F = "f";
	
	public static final  ImmutableList<String> BOOL_START = ImmutableList.of("t","f");
	
	public static final String CHAR_N = "n";

	public static final String DOT_CHAR = ".";
	
	public static final String TRUE = "true";

	public static final String FALSE = "false";

	public static final String NULL = "null";

	public static final String JSON_START_OF_VALUE_KEY_SEP = " At Value Key Seperator";

	public static final String JSON_AT_VALUE_KEY_SEP = " At Value Key Seperator";

	public static final String COMA = ",";

	public static final String JSON_AT_END_VALUE_KEY_SEP = " At End of Key Value Seperator";

	
}
