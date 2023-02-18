import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int m = Integer.valueOf(ps[1]);

		int[] a = new int[m];
		int[] b = new int[m];
		char[] c = new char[m];
		for(int i = 0; i < m; i++) {
			ps = in.readLine().split(" ");
			a[i] = Integer.valueOf(ps[0]);
			b[i] = Integer.valueOf(ps[1]);
			c[i] = ps[2].charAt(0);
		}

		// Construct a TwoSAT problem with 2 variables for each type:
		// i   means type i = 0.5
		// i+n means type i = 2
		TwoSAT sat = new TwoSAT(n*2);
		for(int i = 1; i <= n; i++) {
			// A type cannot be both 0.5 and 2
			sat.AddClause(-i, -(i+n));
		}

		boolean[] nonzero = new boolean[n+1];
		for(int i = 0; i < m; i++) {
			switch(c[i]) {
			case '-':
				// Not very effective, so neither can be 2,
				// and at least one of them needs to be 0.5
				sat.AddClause(-(a[i]+n), -(a[i]+n));
				sat.AddClause(-(b[i]+n), -(b[i]+n));
				sat.AddClause(a[i], b[i]);
				break;
			case '=':
				// 1, so if one is 2 then the other one needs
				// to be 0.5 and vice versa
				sat.AddClause(-a[i], b[i]+n);   // a=0.5 -> b=2
				sat.AddClause(-b[i], a[i]+n);   // b=0.5 -> a=2
				sat.AddClause(-(b[i]+n), a[i]); // b=2   -> a=0.5
				sat.AddClause(-(a[i]+n), b[i]); // a=2   -> b=0.5
				break;
			case '+':
				// Bigger than one, so no 0.5 an at least
				// one of them is 2
				sat.AddClause(-a[i], -a[i]);
				sat.AddClause(-b[i], -b[i]);
				sat.AddClause((a[i]+n), (b[i]+n));
				break;
			}

			if(c[i] != 'x') {
				nonzero[a[i]] = true;
				nonzero[b[i]] = true;
			}
		}

		// Now solve the system
		if(!sat.Satisfiable()) throw new Exception("I was told there would be a solution!");

		// And print answers
		for(int i = 1; i <= n; i++) {
			if(nonzero[i]) {
				System.out.print(sat.IsTrue(i) ? "-" : sat.IsTrue(i+n) ? "+" : "=");
			}
			else {
				System.out.print("x");
			}
		}
		System.out.println();
	}
}

class TwoSAT
{
	private int n;
	private Scc scc;

	public TwoSAT(int n)
	{
		this.n = n;
		this.scc = new Scc(2 * n);
	}

	// 1..n for true, -1..-n for false
	// adding clause v1 or v2
	public void AddClause(int v1, int v2)
	{
		scc.AddEdge(getNum(-v1), getNum(v2));
		scc.AddEdge(getNum(-v2), getNum(v1));
	}

	public boolean Satisfiable()
	{
		scc.FindComponents();
		for (int i = 1; i <= n; i++)
			if (scc.component[getNum(i)] == scc.component[getNum(-i)])
				return false;
		return true;
	}

	public boolean IsTrue(int v)
	{
		return scc.topsort[getNum(v)] > scc.topsort[getNum(-v)];
	}

	private int getNum(int num)
	{
		return num < 0 ? n - num - 1 : num - 1;
	}
}

class Scc
{
	public int n;
	public int[] component;
	public ArrayList<Integer>[] Neighbors, NeighborsR;
	public int[] order;
	public int order_num, actnum;
	public int[] topsort;
	public int tsidx;

	public Scc(int n)
	{
		this.n = n;
		Neighbors = new ArrayList[n];
		NeighborsR = new ArrayList[n];
		for (int i = 0; i < n; i++)
		{
			Neighbors[i] = new ArrayList<Integer>();
			NeighborsR[i] = new ArrayList<Integer>();
		}
	}

	public void AddEdge(int i, int j)
	{
		Neighbors[i].add(j);
		NeighborsR[j].add(i);
	}

	public int FindComponents()
	{
		component = new int[n];
		order = new int[n];
		order_num = 0;

		for (int i = 0; i < n; i++)
			Dfs1(i);

		actnum = 0;
		tsidx = 0;
		topsort = new int[n];
		for (int i = n - 1; i >= 0; i--)
		{
			if (component[order[i]] == -1)
			{
				Dfs2(order[i]);
				actnum++;
			}
		}
		return actnum;
	}

	private void Dfs1(int i)
	{
		if (component[i] != 0) return;
		component[i] = -1;
		for (int adj : Neighbors[i])
			Dfs1(adj);
		order[order_num++] = i;
	}

	private void Dfs2(int i)
	{
		if (component[i] != -1) return;
		component[i] = actnum;
		for (int adj : NeighborsR[i])
			Dfs2(adj);
		topsort[i] = tsidx++;
	}
}
