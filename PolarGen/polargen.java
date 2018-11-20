import java.util.Random;

class PolarGen {

  private boolean nincsTarolt;
  private double tarolt;
  public double kovetkezo;

  public PolarGen() {
    nincsTarolt = true;
  }

  private double kovetkezo() {
    if(nincsTarolt)
    {
      double u1,u2,v1,v2,w;
      int RAND_MAX = 1000;

      do {
        u1 = Math.random() * 1000 / (RAND_MAX + 1.0);
        u2 = Math.random() * 1000 / (RAND_MAX + 1.0);
        v1 = 2 * u1 - 1;
        v2 = 2 * u2 - 1;
        w = v1 * v1 + v2 * v2;
      } while( w > 1);
      double r = Math.sqrt((-2 * Math.log(w)) / w);

      tarolt = r * v2;
      nincsTarolt = !nincsTarolt;

      return r * v1;
    } else {
      nincsTarolt = !nincsTarolt;
      return tarolt;
    }
  }

  public static void main(String[] args)
  {
      PolarGen pg = new PolarGen();

      for(int i = 0; i<10; i++)
      {
        System.out.println(pg.kovetkezo());
      }
  }
}
