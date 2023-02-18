public class PolynomialsJMV {

    public static void main(String[] args) throws java.io.IOException {
        java.io.StreamTokenizer in = new java.io.StreamTokenizer(new java.io.InputStreamReader(System.in));
        in.nextToken();
        int px = (int) in.nval;
        int[] ax = new int[11];
        for (int i = px; i >= 0; i--) {
            in.nextToken();
            ax[i] = (int) in.nval;
        }
        in.nextToken();
        int py = (int) in.nval;
        int[] ay = new int[11];
        for (int i = py; i >= 0; i--) {
            in.nextToken();
            ay[i] = (int) in.nval;
        }

        int p = Math.max(px, py);
        boolean odd = (p & 1) == 1;
        int a = odd ? ax[p] :  ay[p];
        int b = odd ? ay[p] : -ax[p];
        if (a == 0 && b == 0) {
            System.out.println("1 0 0");
            return;
        }
        double[] o = new double[11];
        double[] e = new double[11];
        for (int i = 0; i <= p; i++) {
            o[i] = a * ax[i] + b * ay[i];
            e[i] = b * ax[i] - a * ay[i];
        }
        double t = p == 0 ? 0 : odd ? -o[p - 1] / (p * o[p])
                                    : -e[p - 1] / (p * e[p]);

        for (int i = p; i > 0; i--) {
            double[] d = (i & 1) == 1 ? o : e;
            double[] z = (i & 1) == 1 ? e : o;
            if (Math.abs(z[i]) > 1e-9) {
                System.out.println("0 0 0");
                return;
            }
            double s = 1;
            for (int j = i; j-- > 0; )
                d[j] -= ncp(i, j) * (s *= -t) * d[i];
        }
        System.out.println(a + " " + b + " " + -o[0]);
    }

    private static double ncp(int n, int p) {
        double q = 1;
        while (p > 0)
            q = (q * n--) / p--;
        return q;
    }

}
