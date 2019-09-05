import java.io.*;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader("input.txt"));

        String line;
        ArrayList<Integer> info = new ArrayList<>();
        long summ = 0;

        while ((line = br.readLine()) != null) {
            int next;
            next = Integer.parseInt(line);
            if (info.indexOf(next) == -1) {
                info.add(next);
                summ+=next;
            }
        }
        br.close();

        PrintWriter pwriter = new PrintWriter(new FileWriter("output.txt"));

        pwriter.print(summ);

        pwriter.flush();
        pwriter.close();
    }
}
