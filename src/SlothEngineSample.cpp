#include "SlothEngineApplication.h"

int main(){
   SlothEngineProgramSample slothEngineProgramSample;
   SlothEngineApplication slothEngineApplication = SlothEngineApplication::create(slothEngineProgramSample);
   slothEngineApplication.start();
}