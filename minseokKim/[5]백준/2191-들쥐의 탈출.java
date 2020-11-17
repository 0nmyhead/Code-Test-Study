import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws Exception
	{
		//y�� ���� ���� x�� ������ ����
		//map[y][x]�� �� ���۱��� ���µ� ����� �ɸ��� �ð�
		BufferedReader br = new BufferedReader(new InputStreamReader (System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken()); //�� ����
		int m = Integer.parseInt(st.nextToken()); //���� ����
		int s = Integer.parseInt(st.nextToken());//�� �������� �ð�
		int v = Integer.parseInt(st.nextToken()); //�� �̵��ӵ�
		int d = s*v; //�� ���� ������ ����� �̵� ������ �Ÿ�
		double[][] mouse = new double[n][2];
		double[][] hole = new double[m][2];
		double[][] map = new double[n][m];
		for(int i = 0 ; i < n; i++)
		{
			st = new StringTokenizer(br.readLine());
			mouse[i][0] = Double.parseDouble(st.nextToken());
			mouse[i][1] = Double.parseDouble(st.nextToken());			
		}
		for(int i = 0 ; i < m; i++)
		{
			st = new StringTokenizer(br.readLine());
			hole[i][0] = Double.parseDouble(st.nextToken());
			hole[i][1] = Double.parseDouble(st.nextToken());			
		}
		LinkedList<node> list = new LinkedList(); //�� �� �ִ� ������ ���� ������ ���� �� �� �ֵ��� ���ٰ���.
		int[] visited = new int[m];//�̹� �㰡 ���ִ��� check
		int[] hole_count = new int[m];
		for(int i = 0 ; i < n; i++)
		{
			int count = 0;
			LinkedList<Integer> possible = new LinkedList<Integer>();
			for(int j = 0 ; j < m; j++)
			{				
				map[i][j] = Math.sqrt(Math.pow(mouse[i][0]-hole[j][0], 2)+Math.pow(mouse[i][1]-hole[j][1], 2));
//				System.out.print(map[i][j]+" ");
				if(map[i][j] <= d)
				{
					count++;
					hole_count[j]++;
					possible.add(j);
				}
			}
			node temp = new node(i,count,possible);
			list.add(temp);
//			System.out.println();			
		}
		if(!list.isEmpty())
			Collections.sort(list);	
		Iterator<node> it = list.iterator();
		int live = 0; // �� �� �ִ� ���� �� 
		while(it.hasNext())
		{
			node cur = (node)it.next();
			int min = 101;
			int idx = -1;
			for(int j = cur.hole.size()-1; j>= 0; j--)
			{
				if(visited[cur.hole.get(j)]!=1 && hole_count[cur.hole.get(j)] < min)
				{
					min = hole_count[cur.hole.get(j)];
					idx = j;
				}
			}
			if(idx != -1)
			{
				live++;
				visited[cur.hole.get(idx)] = 1;				
			}
		}
		System.out.println(n-live);
	}
}
class node implements Comparable<node>
{
	int idx; //�� ��° ���ΰ�.
	int count;
	LinkedList<Integer> hole = new LinkedList<Integer>();
	node(int i ,int j,LinkedList<Integer> li)
	{
		idx = i;
		count = j;		
		hole = li;
//		Collections.sort(hole);
	}
	@Override
	public int compareTo(node o) {
		if(this.count < o.count)
			return -1;
		else if(this.count > o.count)
			return 1;
		else
			return 0;
	}
}