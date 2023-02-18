import java.util.*;

public class PaulGreedy {
	static class Node {
		boolean canBeNoEffect = true;
		boolean canBePositive = true;
		boolean canBeNegative = true;
		int colour = -1;
		List<Node> neighbours = new ArrayList<Node>();
		
		boolean isBipartite() {
			for (Node n: neighbours) {
				if (n.colour == -1) {
					n.colour = 1-colour;
					if (!n.isBipartite()) return false;
				}
				if (colour == n.colour) return false;
			}
			return true;
		}

		void eliminatePositive() {
			canBePositive = false;
			for (Node n: neighbours) if (n.canBeNegative) n.eliminateNegative();
		}
		
		void eliminateNegative() {
			canBeNegative = false;
			for (Node n: neighbours) if (n.canBePositive) n.eliminatePositive();
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		
		boolean[] zero = new boolean[n];
		Arrays.fill(zero,true);
		
		Node[] nodes = new Node[n];
		for (int i = 0; i < n; i++) nodes[i] = new Node();

		while (m --> 0) {
			Node a = nodes[sc.nextInt()-1];
			Node b = nodes[sc.nextInt()-1];
			char c = sc.next().charAt(0);

			if (c != 'x') {
				a.canBeNoEffect = b.canBeNoEffect = false;
			}
			if (c == '+') {
				a.canBeNegative = b.canBeNegative = false;
			}
			if (c == '-') {
				a.canBePositive = b.canBePositive = false;
			}
			if (c == '=') {
				a.neighbours.add(b);
				b.neighbours.add(a);
			}
		}
		
		for (Node a: nodes) {
			if (a.canBeNoEffect) continue;
			if (!a.canBePositive) a.eliminatePositive();
			if (!a.canBeNegative) a.eliminateNegative();
			if (a.colour == -1) {
				a.colour = 0;
				if (!a.isBipartite()) {
					a.eliminatePositive();
					a.eliminateNegative();
				}
			}
		}
		
		for (Node a: nodes) {
			if (a.canBeNoEffect) System.out.print('x');
			else if (a.canBePositive && !a.canBeNegative) System.out.print('+');
			else if (!a.canBePositive && a.canBeNegative) System.out.print('-');
			else System.out.print('=');
		}
		System.out.println();
	}
}
