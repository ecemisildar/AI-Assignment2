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
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


#include "armadillo"
#include <initializer_list>

using namespace std;
using namespace arma;

unordered_map<string,vector<pair<string,double>>> graph;

string edges_file = "./visits_domain/edges.txt";


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

  string waypoint_file = "./visits_domain/waypoint.txt";   // change this to the correct path


  parseWaypoint(waypoint_file);
  createEdges(edges_file);
 
}

map<string,double> VisitSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){

  cout << "external called" << endl;

  map<string, double> toReturn;
  map<string, double>::iterator iSIt = initialState.begin();
  map<string, double>::iterator isEnd = initialState.end();
  double dummy;
  double act_cost;
  string region_file = "./visits_domain/region_poses.txt";
  ifstream regionData(region_file);



  map<string, double> trigger;

  for(;iSIt!=isEnd;++iSIt){

    string parameter = iSIt->first;
    string function = iSIt->first;
    double value = iSIt->second;
    string line;
    string waypoint_from;
    string waypoint_to;
    int curr, next;

    function.erase(0,1);
    function.erase(function.length()-1,function.length());
    int n=function.find(" ");

    //cout << "external for loop" << endl;

    if(n!=-1){

      //cout << "external n cond" << endl;
      string arg=function;
      string tmp = function.substr(n+1,5);

      function.erase(n,function.length()-1);
      arg.erase(0,n+1);
      if(function=="triggered"){
        //cout << "external triggered" << endl;
        trigger[arg] = value>0?1:0;
        if (value>0){

      string from = tmp.substr(0,2);   // from and to are regions, need to extract wps (poses)
      string to = tmp.substr(3,2);
      //cout << "external inside triggered" << endl;

      int counter = 0;
     //Open the file
  
      if (regionData.is_open()){
        while (getline(regionData,line) && counter != 2){
         curr=line.find(" [");
         if (line.substr(0,curr).c_str() == from){
            curr=curr+1;
            next=line.find("]",curr);

            waypoint_from = line.substr(curr+1,next-curr-1).c_str();
            counter += 1;
         }
         if(line.substr(0,curr).c_str() == to){
            curr=curr+1;
            next=line.find("]",curr);

            waypoint_to = line.substr(curr+1,next-curr-1).c_str();
            counter += 1;
            
         }

      }
      std::cout << waypoint_from << " " << waypoint_to << endl;
      // Close the file
      regionData.close();

      
        }



    dummy = distance_euc(waypoint_from, waypoint_to, graph);

    }
  }
}else{
  if(function=="dummy"){
    dummy = value;
    //cout << "external dummy" << endl;
    //cout << "value: " << value << endl;

  }else if(function=="act-cost"){
    act_cost = value;
    //cout << "external act-cost" << endl;
    //cout << "value: " << value << endl;
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
       return external;
     }

     void VisitSolver::createEdges(string edges_file){

    	int k = 0;
      // Open the file
       ofstream edgesData(edges_file);
       if (edgesData.is_open()){

        for (auto pair1 : fixed_waypoint) {
          const std::string& waypoint1 = pair1.first;
          const std::vector<int>& poses1 = pair1.second;

          for (auto pair2 : fixed_waypoint) {
            const std::string& waypoint2 = pair2.first;
            const std::vector<int>& poses2 = pair2.second;

            //cout << waypoint1 << "," << waypoint2 << endl;


            if (waypoint1 != waypoint2) {
              float distance = sqrt(std::pow((poses1[0]-poses2[0]),2)+ std::pow((poses1[1]-poses2[1]),2));
                if (distance < 1.5 && k < 4) {
                    edgesData << waypoint1 << " " << waypoint2 << " " << distance << endl;   
                    k++;
                }
            }
          }
          k = 0;
        }

        // Close the file
      }    
      
        edgesData.close();

        string source, destination;
        double distance;

        ifstream edges(edges_file);

        while(!edges.eof()){
          
          //sleep(2);
          edges>>source>>destination>>distance;
          //cout<< source << " " << destination << " " << distance <<endl; 
          graph[source].push_back(make_pair(destination,distance));
        }


    edges.close();

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
         //cout << pose1 << "," << pose2 << "," << waypoint_name << endl;
       }
       parametersFile.close();
     }

   }



double VisitSolver::distance_euc( string from, string to, unordered_map<string,vector<pair<string,double>>> graph){

  unordered_map<string,double> dist;
  string next_node;
  double next_distance;

  for (const auto& n : graph){
    dist[n.first]=999999999;
  }
  
  dist[from]=0;

  priority_queue<pair<double,string>, vector<pair<double,string>>, greater<pair<double,string>>> p;

  p.push(make_pair(0,from));

  while(!p.empty()){

    int current_dist=p.top().first;
    string current_node=p.top().second;
    
    p.pop();

    if(current_node==to){ 
            cout << "minimal path found with: " << current_dist <<endl; 
      	    return current_dist;
      }

    for(const auto& g:graph[current_node]){
      next_node=g.first;
      cout << "current node " << current_node << " next node " << next_node <<endl; 
      next_distance=g.second;

      if(dist[next_node]>current_dist+next_distance){
        dist[next_node]=current_dist+next_distance;
        p.push(make_pair(current_dist+next_distance,next_node));
      }
    }
  }
  

  return 0;
} 






