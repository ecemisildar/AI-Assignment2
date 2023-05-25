    /*
     <one line to give the program's name and a brief idea of what it does.>
     Copyright (C) 2015  <copyright holder> <email>
     
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.
     */


#include "VisitSolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "armadillo"
#include <initializer_list>

using namespace std;
using namespace arma;



    //map <string, vector<double> > region_mapping;

extern "C" ExternalSolver* create_object(){
  return new VisitSolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
  delete externalSolver;
}

VisitSolver::VisitSolver(){

}

VisitSolver::~VisitSolver(){

}

void VisitSolver::loadSolver(string *parameters, int n){
  starting_position = "r0";
  string Paramers = parameters[0];

  char const *x[]={"dummy"};
  char const *y[]={"act-cost","triggered"};
  parseParameters(Paramers);
  affected = list<string>(x,x+1);
  dependencies = list<string>(y,y+2);

  string waypoint_file = "/home/ecem/Documents/ai2/AI-Assignment2/AI-Assignment2/visits_domain/waypoint.txt";   // change this to the correct path
  string edges_file = "/home/ecem/Documents/ai2/AI-Assignment2/AI-Assignment2/visits_domain/edges.txt";


  parseWaypoint(waypoint_file);
  createEdges(edges_file);
 
}

map<string,double> VisitSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){

  map<string, double> toReturn;
  map<string, double>::iterator iSIt = initialState.begin();
  map<string, double>::iterator isEnd = initialState.end();
  double dummy;
  double act_cost;


  map<string, double> trigger;

  for(;iSIt!=isEnd;++iSIt){

    string parameter = iSIt->first;
    string function = iSIt->first;
    double value = iSIt->second;

    function.erase(0,1);
    function.erase(function.length()-1,function.length());
    int n=function.find(" ");

    if(n!=-1){
      string arg=function;
      string tmp = function.substr(n+1,5);

      function.erase(n,function.length()-1);
      arg.erase(0,n+1);
      if(function=="triggered"){
        trigger[arg] = value>0?1:0;
        if (value>0){

      string from = tmp.substr(0,2);   // from and to are regions, need to extract wps (poses)
      string to = tmp.substr(3,2);


     // distance_euc(from, to);

    }
  }
}else{
  if(function=="dummy"){
    dummy = value;

  }else if(function=="act-cost"){
    act_cost = value;
                 } //else if(function=="dummy1"){
                    //duy = value;              
                    ////cout << parameter << " " << value << endl;
                 //}
                 }
               }


               double results = calculateExtern(dummy, act_cost);
               if (ExternalSolver::verbose){
                cout << "(dummy) " << results << endl;
              }

              toReturn["(dummy)"] = results;


              return toReturn;
            }

            list<string> VisitSolver::getParameters(){

              return affected;
            }

            list<string> VisitSolver::getDependencies(){

              return dependencies;
            }


            void VisitSolver::parseParameters(string parameters){

              int curr, next;
              string line;
              ifstream parametersFile(parameters.c_str());
              if (parametersFile.is_open()){
                while (getline(parametersFile,line)){
                 curr=line.find(" ");
                 string region_name = line.substr(0,curr).c_str();
                 curr=curr+1;
                 while(true ){
                  next=line.find(" ",curr);
                  region_mapping[region_name].push_back(line.substr(curr,next-curr).c_str());
                  if (next ==-1)
                   break;
                 curr=next+1;

               }                
             }

           }
         }

         double VisitSolver::calculateExtern(double external, double total_cost){
       //float random1 = static_cast <float> (rand())/static_cast <float>(RAND_MAX);
       double cost = 2;//random1;
       return cost;
     }

     void VisitSolver::createEdges(string edges_file){

    
      // Open the file
       ofstream edgesData(edges_file);
       if (edgesData.is_open()){

        for (auto pair1 : fixed_waypoint) {
        const std::string& waypoint1 = pair1.first;
        const std::vector<int>& poses1 = pair1.second;

        for (auto pair2 : fixed_waypoint) {
            const std::string& waypoint2 = pair2.first;
            const std::vector<int>& poses2 = pair2.second;

            cout << waypoint1 << "," << waypoint2 << endl;


            if (waypoint1 != waypoint2) {
              float distance = sqrt(std::pow((poses1[0]-poses2[0]),2)+ std::pow((poses1[1]-poses2[1]),2));
                if (distance < 1.5) {
                    edgesData << waypoint1 << ", " << waypoint2 << " - " << distance << endl;   
                }
            }
         }
        }
      // Close the file
      edgesData.close();

      }
        
        
    }


        

     void VisitSolver::parseWaypoint(string waypoint_file){

       int curr, next;
       string line;
       int pose1, pose2;
       ifstream parametersFile(waypoint_file);
       if (parametersFile.is_open()){
        while (getline(parametersFile,line)){ // ERROR: READING EOF
         curr=line.find("[");
         string waypoint_name = line.substr(0,curr).c_str();

         curr=curr+1;
         next=line.find(",",curr);

         pose1 = (int)atof(line.substr(curr,next-curr).c_str());
         curr=next+1; next=line.find(",",curr);

         pose2 = (int)atof(line.substr(curr,next-curr).c_str());
         curr=next+1; next=line.find("]",curr);


         fixed_waypoint[waypoint_name] = vector<int> {pose1, pose2};
         cout << pose1 << "," << pose2 << "," << waypoint_name << endl;
       }
       parametersFile.close();
     }

   }



   



  //void VisitSolver::distance_euc( string from, string to){
  //} 







