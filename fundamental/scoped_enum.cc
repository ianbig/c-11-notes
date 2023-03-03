enum class Ian; // forward declaration


int main() {
  enum Color { black, white, red};
  Color c = white;

  // auto white = true; namespace pollution

  enum class Class { math, pe, history };
  Class classroom = Class::math;

  // strong type
  if (c < 14.5) { // type conversion
    
  }

  // if (classroom < 14.5) {

  // }

}