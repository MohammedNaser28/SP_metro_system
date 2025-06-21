#include<string>
#include"structures.h"
#include"global.cpp"




void buildGraph() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            graph[i][j] = -1;

    for (int j = 0; j < NUM_LINES; j++) {
        for (int i = 0; i < MAX_STATIONS_PER_LINE - 1; i++) {
            if (allStations[i][j].name != "-" && allStations[i + 1][j].name != "_") {
                int from = allStations[i][j].number;
                int to = allStations[i + 1][j].number;
                graph[from][to] = j + 1;
                graph[to][from] = j + 1;
            }
        }
    }
    //this is the constant stations 
    graph[19][50] = 2; graph[50][19] = 1;
    graph[52][99] = 3; graph[99][52] = 2;
    graph[20][100] = 3; graph[100][20] = 1;
    graph[46][115] = 3;graph[115][46] = 2;

}

bool bfs(int start, int end, int parent[]) {
    bool visited[MAX] = { false };
    int queue[MAX], front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = true;
    parent[start] = -1;

    while (front < rear) {
        int current = queue[front++];
        if (current == end) return true;

        for (int i = 1; i <= num_stations; i++) {
            if (graph[current][i] != -1 && !visited[i]) {
                visited[i] = true;
                parent[i] = current;
                queue[rear++] = i;
            }
        }
    }
    return false;
}

void calc_kit_kat_index()
{
    for (int i = 0;i < MAX_STATIONS_PER_LINE;i++)
    {
        if (allStations[i][2].name == "Kit_Kat.")
        {
            kit_kat_index = allStations[i][2].number;
            break;
        }

    }
    for (int i = 0;i < 20;i++)
    {
        if (allStations[(kit_kat_index - (2 * MAX_STATIONS_PER_LINE)) + i][2].name == "Switching.")
        {
            switching_index = allStations[(kit_kat_index - (2 * MAX_STATIONS_PER_LINE)) + i][2].number;
            break;
        }
    }
}



int find_st_num(string start)
{
    for (int i = 0;i < NUM_LINES;i++)
    {

        for (int j = 0;j < MAX_STATIONS_PER_LINE;j++)
        {
            if (start == allStations[i][j].name)
                return allStations[i][j].number;

        }
    }
}

string findShortestPath(int start, int end) {
    int parent[MAX];
    string path_string;
    calc_kit_kat_index();
    if ((start > kit_kat_index && start < switching_index && end > switching_index) ||
        (end > kit_kat_index && end<switching_index && start>switching_index))
    {
        path_string+="\n--- Route ---\n";
        if (start < switching_index)     ///start in rod elfarag branch
        {
            int cnt = start - kit_kat_index;
            for (int i = cnt - 1;i >= -1;i--)
            {
                stationcnt++;
                path_string+=("-> "+ allStations[kit_kat_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name + '\n');
            }

            for (int i = 0;i < (end - switching_index);i++)
            {
                stationcnt++;
                path_string += ("-> " + allStations[i + switching_index - (2 * MAX_STATIONS_PER_LINE)][2].name +"\n");
            }

        }
        else if (start > switching_index)        ///start in cairo uni branch
        {
            int cnt = start - switching_index;
            for (int i = cnt - 1;i >= 0;i--)
            {
                stationcnt++;
                path_string += ("-> " + allStations[switching_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name +"\n");
            }
            for (int i = -1;i < (end - kit_kat_index);i++)
            {
                stationcnt++;
                path_string += ("-> " + allStations[kit_kat_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name + "\n");
            }

        }
        return path_string;
    }
    if (!bfs(start, end, parent)) {
        path_string+="No path found.\n";
        return path_string;
    }

    int path[MAX], count = 0;
    for (int at = end; at != -1; at = parent[at])
        path[count++] = at;

   path_string+="\n--- Route ---\n";

    int lastLine = -1;
    string lastName = "";

    for (int i = count - 1; i > 0; i--) {
        int curr = path[i];
        int next = path[i - 1];

        string currName = allStations[(curr - 1) % MAX_STATIONS_PER_LINE][(curr - 1) / MAX_STATIONS_PER_LINE].name;
        string nextName = allStations[(next - 1) % MAX_STATIONS_PER_LINE][(next - 1) / MAX_STATIONS_PER_LINE].name;

        if (currName == nextName) continue;

        int line = graph[curr][next];

        if (line != lastLine && lastLine != -1) {
            path_string+=( "-- Switch to Line " + to_string(line) + " --\n");
        }

        path_string += ("-> " + currName + "\n");
        lastLine = line;
        lastName = currName;
    }


    string lastStationName = allStations[(end - 1) % MAX_STATIONS_PER_LINE][(end - 1) / MAX_STATIONS_PER_LINE].name;
    if (lastStationName != lastName) {
        path_string += ("-> " + lastStationName + "\n");
    }

    return path_string;
}