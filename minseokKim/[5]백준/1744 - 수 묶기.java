import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int[] arr = new int[n];
		for(int i = 0; i < n; i++)
		{
			arr[i] = Integer.parseInt(br.readLine());
		}
		Arrays.sort(arr);
		int sum =0;
		for(int i = n-1; i >=0; i--)
		{
			int temp = arr[i];
			//��*��,�Ѵ� 1���� Ŭ�� ��
			if(i>0 && arr[i] >0 )
			{
				if(arr[i-1] >0)
				{
					if(arr[i] == 1 || arr[i-1] == 1)
					{
						sum+=temp;
						continue;
					}
					else
					{
						temp*=arr[i-1];
						i--;
						sum+=temp;
						continue;	
					}				
				}
				else
				{
					sum+=temp;
					continue;
				}
			}
			//��*�� �н�
			else if(i>0 && arr[i] >0 && arr[i-1] < 0)
			{
				sum+=temp;
				continue;				
			}
			//���϶��� �ڿ��� Ȧ�� ������� üũ
			else if(i>0 && arr[i] == 0)
			{
				//���϶� �ڿ��� Ȧ���̸� �ڿ��� �� ������
				//���϶� �ڿ��� ¦���̸� �׳� �Ȱ��ϰ� �н�
				if(i%2 == 0)
				{
					continue;
				}
				else
				{
					temp*=arr[i-1];
					i--;
				}
				sum+=temp;
				continue;
			}
			//��*��
			else if(i > 0 && arr[i] <0 && arr[i-1]<0)
			{
				if(i%2 == 0)
				{
					sum+=temp;
					continue;
				}
				else
				{
				temp*=arr[i-1];
				i--;
				sum+=temp;
				continue;
				}
			}
			else
			{
				sum+=temp;
				continue;
			}
		}
		System.out.println(sum);
	}
}
