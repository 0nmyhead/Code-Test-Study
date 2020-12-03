import java.util.*;
import java.io.*;

public class Main {
/*

s*a+b
(s*a +b)*a+b -> sa^2+ab+b
((s*a +b)*a+b)*a+b -> (sa^2+ab+b)*a+b -> sa^3+a^2b+ab+b
�̷��� �� �ʿ䰡 �ִ°�? ����

1*a+b = 4
4*a+b = 13���� a,b����
�׸��� �Էº��� ~ n����*a+b�ϸ鼭 a,b�� ��� ���� ������ �����Ǹ� n+1���� �� ����
���� 3 3 3 3 4 => a,b�� ���� �ȵ� -> B

1 2 => 3���� 4���� �� : A
�׷��� n<=2�϶��� A����ҷ��µ�
���� 1 1�̴�? -> �������� 1�ΰ� �� �� ����
*/
	public static void main(String[] args)throws Exception
	{
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int[] num = new int[n+1];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0 ; i < n; i++)
		{
			num[i] = Integer.parseInt(st.nextToken());
		}
		int a = 0;
		int b = 0;
		if(n<=2)
		{
			if(n ==2 && num[0] == num[1])
				System.out.println(num[0]);
			else
				System.out.println("A");
			return;
		}
		else
		{
			if(num[1]-num[0] != 0)
				a = (num[2]-num[1])/(num[1]-num[0]);
			else a = 0;
			b = num[1]-(num[0]*a);
		}
		int cur_a = 0;
		int cur_b = 0;
		
		for(int i = 1; i< n-2; i++)
		{
			if(num[i+1] - num[i] != 0)
			cur_a = (num[i+2]-num[i+1])/(num[i+1]-num[i]);
			else
				cur_a = 0;
			cur_b = num[i+1]-(num[i]*a);
			if(cur_a!=a ||cur_b != b )
			{
				System.out.print("B");
				return;
			}
		}
		if(num[n-2]*a+b != num[n-1])
		{
			System.out.print("B");
			return;
		}
		System.out.println(((long)num[n-1])*a+b);
	}
}
