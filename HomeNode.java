
import net.dongliu.requests.body.*;

public class HomeNode{
  private int    numRelays;
  private String ipAddr;
  private String name;
  
  public HomeNode(String name, String ipAddr, int numRelays){
    this.name      = name;
    this.ipAddr    = ipAddr;
    this.numRelays = numRelays;
  }
  
  public void setRelay(int relay, boolean state){
    if((relay < numRelays) && (relay > 0)){
        requests.get(String.format("http://%s/re%d_%s", ipAddr, relay, state))).send();
    }
  }

  public String getTemp(){
    String temp = "N/A";
    
    return temp;
  }

}
