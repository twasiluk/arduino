import org.gicentre.utils.stat.*;    // For chart classes.
import processing.serial.*;

XYChart lineChart, lineChart2;
Serial myPort;
int xPos = 1;
int x = 1, y = 1;
float[] liveSec, liveTemp;
int liveIdx = 0;
float labelTemp = 0;

void setup()
{
  liveSec = new float[400];
  liveTemp = new float[400];
  
  println(Serial.list());  
  myPort = new Serial(this, Serial.list()[0], 9600);  
  myPort.bufferUntil('\n');  
  
  size(1000,500);
  smooth();
  noLoop();
  
  PFont font = createFont("Helvetica",11);
  textFont(font,10);  
}

void createGraph()
{
  // Both x and y data set here.  
  lineChart = new XYChart(this);
  lineChart.setData(new float[] {0,   30,  60, 120, 150, 180, 195, 210, 240},
                    new float[] {20, 100, 150, 200, 235, 250, 235, 200, 80});
  
  // Axis formatting and labels.
  lineChart.showXAxis(true); 
  lineChart.showYAxis(true); 
  lineChart.setMinY(0);
  lineChart.setMaxY(300);
  lineChart.setMaxX(300);
    
  lineChart.setYFormat("###C");  // Monetary value in $US
  lineChart.setXFormat("000");      // Year
  
  // Symbol colours
  lineChart.setPointColour(color(180,50,50,100));
  lineChart.setPointSize(5);
  lineChart.setLineWidth(2);
  
  
  lineChart2 = new XYChart(this);
  lineChart2.setData(stripZeroes(liveSec), stripZeroes(liveTemp));
  
  // Axis formatting and labels.
  lineChart2.showXAxis(true); 
  lineChart2.showYAxis(true); 
  lineChart2.setMinY(0);
  lineChart2.setMaxY(300);
  lineChart2.setMaxX(300);
  
  lineChart2.setYFormat("###C");  // Monetary value in $US
  lineChart2.setXFormat("000");      // Year
  
  // Symbol colours
  lineChart2.setPointColour(color(110,10,10,100));
  lineChart2.setPointSize(5);
  lineChart2.setLineWidth(2);
}

void draw()
{
  background(255);
  textSize(9);
  lineChart.draw(15,15,width-30,height-30);
  lineChart2.draw(15,15,width-30,height-30);
  
  // Draw a title over the top of the chart.
  fill(120);
  textSize(20);
  
  String[] label = new String[3]; 
  label[0] = "Reflow Profile"; 
  label[1] = str(round(labelTemp)); 
  label[2] = "C"; 
  String myLabel = join(label, " "); 
  
  text(myLabel, 100, 30);  
  
  
  //textSize(11);
  //text("Gross domestic product measured in inflation-corrected $US", 70,45);
}

void serialEvent (Serial myPort)
{
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  print(inString);
 
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    String[] list = split(inString, ',');
 
    // convert current temp to float
    float currentTemp = float(list[1]);
    labelTemp = currentTemp;
    
    // draw the point
    //draw();
    liveSec[liveIdx] = float(list[0]);
    liveTemp[liveIdx++] = float(list[1]);
    createGraph();
    redraw();
  }
}

float[] stripZeroes(float[] data)
{
  //println(data);
  int i = data.length;
  int zero = 0;
  for (int j = 0; j < i; j++) {
    //print(j); print(" = ");  println(data[j]);
    if (data[j] == 0) {
      zero = j;
      break;
    }
  }
  //print("found zeros at "); println(zero);
  
  float[] datar = new float[zero];
  for (int j = 0; j < zero; j++) {
    datar[j] = data[j];
  }
  //println(datar);
  return(datar);
}
