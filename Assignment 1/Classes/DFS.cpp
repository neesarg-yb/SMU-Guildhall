//
//  use: map<Node *> visitedMap;
//  use: Node* v;
//  use: find(visitedMap.begin(), visitedMap.end(), v)
//    -> to chech whether it is visited or not
//

Node* findThisNodeUsingDFS(string searchingForNode) {

  // It will contain Nodes which are already visited
  vector<Node *> *visitedMap;

  // Call the recursive helper function to find that Node v
  return DFSUtil(this, searchingForNode, visitedMap);
}

Node* DFSUtil(Node *findFrom, string searchingForNode, vector<Node *> *visitedMap) {
  Node* result = NULL;
  // Mark the current node as visited
  visitedMap.push_back(findFrom);

  if(findFrom->name == searchingForNode) {
    // Node found; return it.
    result = findFrom;
    return result;
  }

  // Recur for all the childNodes of findFrom Node
  for(int i = findFrom->childNode.size()-1; i>=0; i--) {
    /*
     * If childNode[i] not in visitedMap
     */
        result = DFSUtil(childNode, searchingForNode, visitedMap);
        if(result != NULL) { break; }
  }

  return result;
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}

int main() {
  cout << "Following is Depth First Traversal (starting from vertex 2) \n";
  g.DFS(2);

  return 0;
}
