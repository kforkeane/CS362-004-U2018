import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.Random;

//Junit Test 4

public class RandomUrlValidatorTest {

  @Before
  public void setUp() throws Exception {
  }

  @After
  public void tearDown() throws Exception {
  }

  @Test
  public void test() {

    Random rand = new Random();
    //instantiate urlValidator, testing main five components
    int passed = 0, failed = 0;
    
    UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
    String[] scheme = { "http://", "ftp://", "https://", "no", "124", "#@#1" }; //3-5 invalid
    String[] authority = { "www.neopets.com", "0.0.0.0", "mega.nz", "-1.-1.-1", "234@s", "" }; //3-5 invalid
    String[] port = { ":28", ":65535", "", ":-100", ":wrong", "-!ADS" }; //3-5 invalid
    String[] path = { "", "/blah", "/blah/", "/..", "//..", "/../" }; //3-5 invalid
    String[] query = { "", "?user=apache", "?q=query&56=num&quote=yes", "invalid", "01231", ")!(@*" }; //3-5 invalid
    String[] fragment = { "", "#jump", "#validfrag123", "nohashmark", "$*)(a", "=-=-" }; //3-5 invalid
    
    for (int i = 0; i < 2000; i++){
      
      int schemeChoice = rand.nextInt(6);
      int authChoice = rand.nextInt(6);
      int portChoice = rand.nextInt(6);
      int pathChoice = rand.nextInt(6);
      int queryChoice = rand.nextInt(6);
      int fragChoice = rand.nextInt(6);
      
      boolean theoretical = true; //expected value
      
      if (schemeChoice > 2 || authChoice > 2 || portChoice > 2 || pathChoice > 2 || queryChoice > 2 || fragChoice > 2){
        theoretical = false;
      }
      
      //build URL
      
      String url = scheme[schemeChoice] + authority[authChoice] + port[portChoice] + path[pathChoice] + query[queryChoice] + fragment[fragChoice];
      boolean result = urlVal.isValid(url); //testing url with url validator, experimental value
      
      // if (result){  //for debugging purposes
      //   System.out.println("result expected to be true");
      // }
      // else System.out.println("result expected to be false");
      
      
      if (result != theoretical){
        System.out.println("test failed with string " + url);
        failed++;
      }
      else {
        System.out.println("test passed with string " + url);
        passed++;
      }
    }
    
    System.out.println("tests passed: " + passed + " tested failed: " + failed);
  
    
  }

}
