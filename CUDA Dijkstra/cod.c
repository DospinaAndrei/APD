#include<stdio.h>

#include<stdlib.h>

#include<limits.h>

#define size 1000

struct Graph

{

    int start;

    int end[size];

    int weight[size];

    int count;

};

File *fp;

int no_of_nodes,no_of_edges,source;

__global__ void kernel(int *d_mask,int *d_dist,int d_minindex,struct Graph *d_graph)

{

    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    d_mask[d_min_index]=true;

    if(tid<d_graph[d_min_index].count)

    {

        if(d_dist[d_graph[d_min_index].end[tid]>d_dist[d_min_index]+d_graph[d_min_index].weight[tid])

            d_dist[d_graph[d_min_index].end[tid]=d_dist[d_min_index]+d_graph[d_min_index].weight[tid];

    }

}

int mindistance(int dist[],int mask[])

{

  int min=INT_MAX;

  for(i=0;i<no_of_nodes;i++)

  {

      if(mask[i]==false&&dist[i]<min)

      {

          min = dist[i];

      }

  }

  return min;

}

int minindex(int dist[],int mask[])

{

  int min=INT_MAX,min_index;

  for(i=0;i<no_of_nodes;i++)

  {

      if(mask[i]==false&&dist[i]<min)

      {

          min = dist[i];

          min_index=i;

      }

  }

  return min_index;

}

int main()

{

      //File read

    printf(“Reading File\n”);

static char *input_file_name=”SampleGraph.txt”;

    printf(“Input file: %s\n”, input_file_name);

fp = fopen(input_file_name,”r”);

if(!fp)

{

 printf(“Error Reading graph file\n”);

 return;

}

fscanf(fp,”%d”,&no_of_nodes);

struct Graph h_graph[no_of_nodes+1];

//Inputting from file

for(int i=0;i<no_of_nodes;i++)

    {

        h_graph[i].count=0;

        h_graph[i].start=i;

    }

fscanf(fp,”%d”,&no_of_edges);

fscanf(fp,”%d”,&source);

for(int i=0;i<no_of_edges;i++)

    {

      fscanf(fp,”%d”,&h_graph[i].start);

      fscanf(fp1,”%d”,&h_graph[h_graph[i].start].end[h_graph[h_graph[i].start].count]);

      fscanf(fp1,”%d”,&h_graph[h_graph[i].start].weight[h_graph[h_graph[i].start].count]);

      h_graph[h_graph[i].start].count++;

    }

    //Host memory allocation

int h_dist[no_of_nodes+1];

memset(h_dist,INT_MAX,sizeof(dis));

bool h_mask[no_of_nodes+1];

memset(mask,false,sizeof(dis));

h_dist

= 0;

    //Gpu memory allocation

    Graph* d_graph;

    cudaMalloc( (void**) &d_graph, sizeof(Graph)*no_of_nodes);

    cudaMemcpy( d_graph, h_graph, sizeof(Graph)*no_of_nodes, cudaMemcpyHostToDevice);

    int* d_dist;

    cudaMalloc((void**) &d_dist, sizeof(int)*no_of_nodes);

    cudaMemcpy(d_dist, h_dist, sizeof(int)*no_of_nodes, cudaMemcpyHostToDevice);

int d_minIndex;

    cudaMalloc( (void**) &d_minIndex, sizeof(int));

    cudaMemcpy( d_minIndex, h_minIndex, sizeof(int), cudaMemcpyHostToDevice);

    bool* d_mask;

    cudaMalloc( (void**) &d_mask, sizeof(bool)*no_of_nodes);

    cudaMemcpy( d_mask, h_mask, sizeof(bool)*no_of_nodes, cudaMemcpyHostToDevice);

    for(i=0;i<no_of_nodes;i++)

    {

       int h_minIndex = minindex(h_dist,h_mask);

       int h_minDis = mindistance(h_dist,h_mask);

       if(h_min_dis==INT_MAX)

       {

           //no node needs to be updated

           break;

       }

       //thread and block size

       int no_of_block = 1,no_of_threads = h_graph[minIndex].count;

       if(no_of_threads>256)

       {

           no_of_block = ceil(no_of_threads/256);

       }

       Kernel<<<no_of_block,no_of_threads>>(d_mask,d_dist,d_minIndex,d_graph);

       cudaMemcpy( h_dist, d_dist, sizeof(int)*no_of_nodes, cudaMemcpyDeviceToHost);

    }

    //Output File

    FILE *fpo = fopen(“result.txt”,”w”);

    for(i=0;i<no_of_nodes;i++)

fprintf(fpo,”%d) cost:%d\n”,i,h_dist[i]);

fclose(fpo);

printf(“Result stored in result.txt\n”);

    return 0;

}