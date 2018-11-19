public class PortScanner {

    public static void main(String[] args) {

      int k = 0;
        for(int i=0; i<1024; ++i)

            try {

                java.net.Socket socket = new java.net.Socket(args[0], i);

                k++;

                System.out.println(i + " figyeli." );

                socket.close();

            } catch (Exception e) {
              //Ha nem sikerül kapcsolatot létesíteni, akkor nem figyeli

            }

            System.out.println(k + " portot figyel a(z) " + args[0] + " IP-n.");
    }

}
