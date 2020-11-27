import java.util.*;
import java.io.*;
public class Main {
	public static int[] on_dp;
	public static int[] off_dp;
	public static LinkedList[] link;
	public static int[] people;
	public static boolean[] visited;
//	public static boolean[] off_visited;

	public static void main(String[] args)throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		people =new int[n];
		StringTokenizer st = new StringTokenizer(br.readLine());
		link = new LinkedList[n];
		on_dp = new int[n];
		off_dp = new int[n];
		visited = new boolean[n];
		for(int i = 0; i < n; i++)
		{
			people[i] = Integer.parseInt(st.nextToken());
			link[i] = new LinkedList<Integer>();
			on_dp[i] = -1;
			off_dp[i] = -1;
		}
		for(int i = 0; i < n-1; i++)
		{
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			link[a-1].add(b-1);
			link[b-1].add(a-1);
		}
		visited[0] = true;
		int zero_on = on_dfs(0);
		int zero_off = off_dfs(0);
		visited[0] = false;
		System.out.println(Math.max(zero_on,zero_off));
	}	
	public static int off_dfs(int cur) //cur���� ������.(��������� �����Ǿ���.)
	{	
		//parent�� -1�̸� ���� 1�̸� ����
		//���� ������ �ڽĵ��� �����ų� �����ų� ��� x.
		//�ٵ� �� �θ� ���� ���·� ������ �ڽĵ��� �� ��������.
			//�̶�� ���������� �θ�� �Ű澵 �ʿ䰡 ������!
		int value = 0;
		if(link[cur].size() == 0)
			return 0;
		if(off_dp[cur] > 0)
			return off_dp[cur];
//		if(parent_on == true)
		{
			Iterator it = link[cur].iterator();
			while(it.hasNext())
			{
				int next = (int)it.next();
				int temp1 = -1;
				int temp2 = -1;
				if(visited[next])
				{
					continue;
				}
				else
				{
					visited[cur] = true;
					temp1 = on_dfs(next);
					temp2 = off_dfs(next);
					visited[cur] = false;
				}
				value+= Math.max(temp1, temp2);
			}
		}
//		else
//		{
//			Iterator it = link[cur].iterator();
//			while(it.hasNext())
//			{
//				int next = (int)it.next();
//				if(visited[next])
//					continue;
//				visited[cur] = true;
//				value+= on_dfs(next);
//				visited[cur] = false;
//			}			
//		}
		return off_dp[cur] = value;
	}
	public static int on_dfs(int cur)
	{	
		//�θ�� ������� ���� ������ -> �ڽ��� �� ������
		
		int value = people[cur];
		if(link[cur].size() == 0)
			return 0;
		if(on_dp[cur] > 0)
			return off_dp[cur];

		Iterator it = link[cur].iterator();
		while(it.hasNext())
		{
			int next = (int) it.next();
			if(visited[next])
				continue;
			visited[cur] = true;
			value+= off_dfs(next);
			visited[cur] = false;
		}
		return on_dp[cur] = value;
	}
}
