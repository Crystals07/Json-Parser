package parser.utils;

public class MutableInt {
	private Integer num;
	
	public MutableInt() {
		this.num = 0;
	}
	
	public void Increment() {
		num = num+1;
	}
	
	public boolean equals(Integer index) {
		return num.equals(index);
	}

	public Integer getInt() {
		// TODO Auto-generated method stub
		return num;
	}
	
	public String toString() {
		return num.toString();
	}

	public void setNum(int i) {
		// TODO Auto-generated method stub
		this.num = i;
	}
}
