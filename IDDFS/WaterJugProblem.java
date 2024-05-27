package UninformedSearch.IDDFS;

import java.util.*;

public class WaterJugProblem {
    private static final int JUG1_CAPACITY = 3, JUG2_CAPACITY = 5, TARGET = 4;

    public static void main(String[] args) {
        WaterJugProblem problem = new WaterJugProblem();
        System.out.println("\nIDDFS:");
        printResult(problem.iddfs(), problem.iddfsStates);
    }

    static class State {
        int jug1, jug2;
        String action;

        State(int jug1, int jug2, String action) {
            this.jug1 = jug1;
            this.jug2 = jug2;
            this.action = action;
        }

        public String toString() {
            return "jug1: " + jug1 + ", jug2: " + jug2 + " - " + action;
        }
    }

    int dlsStates = 0, iddfsStates = 0;

    private List<State> getNeighbors(State state) {
        List<State> neighbors = new ArrayList<>();
        int jug1 = state.jug1, jug2 = state.jug2;
        neighbors.add(new State(JUG1_CAPACITY, jug2, "Fill Jug1"));
        neighbors.add(new State(jug1, JUG2_CAPACITY, "Fill Jug2"));
        neighbors.add(new State(0, jug2, "Empty Jug1"));
        neighbors.add(new State(jug1, 0, "Empty Jug2"));
        neighbors.add(new State(Math.max(0, jug1 - (JUG2_CAPACITY - jug2)), Math.min(JUG2_CAPACITY, jug1 + jug2),
                "Pour Jug1 -> Jug2"));
        neighbors.add(new State(Math.min(JUG1_CAPACITY, jug1 + jug2), Math.max(0, jug2 - (JUG1_CAPACITY - jug1)),
                "Pour Jug2 -> Jug1"));
        return neighbors;
    }

    private List<State> constructPath(Map<State, State> parentMap, State goal) {
        List<State> path = new ArrayList<>();
        for (State at = goal; at != null; at = parentMap.get(at))
            path.add(at);
        Collections.reverse(path);
        return path;
    }

    public List<State> dls(int limit) {
        return dlsRecursive(new State(0, 0, "Initial State"), new HashSet<>(), new HashMap<>(), limit);
    }

    private List<State> dlsRecursive(State current, Set<State> visited, Map<State, State> parentMap, int limit) {
        dlsStates++;
        if (current.jug1 == TARGET || current.jug2 == TARGET)
            return constructPath(parentMap, current);
        if (limit == 0)
            return Collections.emptyList();
        visited.add(current);
        for (State neighbor : getNeighbors(current)) {
            if (!visited.contains(neighbor)) {
                parentMap.put(neighbor, current);
                List<State> result = dlsRecursive(neighbor, visited, parentMap, limit - 1);
                if (!result.isEmpty())
                    return result;
            }
        }
        visited.remove(current);
        return Collections.emptyList();
    }

    public List<State> iddfs() {
        List<State> result;
        int depth;
        for (depth = 0;; depth++) {
            dlsStates = 0;
            result = dls(depth);
            iddfsStates += dlsStates;
            if (!result.isEmpty())
                return result;
        }
    }

    private static void printResult(List<State> result, int statesExplored) {
        if (result.isEmpty()) {
            System.out.println("No solution found.");
        } else {
            for (State state : result) {
                System.out.println(state);
            }
            System.out.println("Total states explored: " + statesExplored);
        }
    }
}
