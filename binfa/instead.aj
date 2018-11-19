public aspect instead {

  before(char c) : call(public void addChar(char)) && args(c) {
    System.out.println("-- "+ c +" előtt--");
  }

  after(char c) : call(public void addChar(char)) && args(c) {
    System.out.println("-- "+ c +" után--" );
  }
}
