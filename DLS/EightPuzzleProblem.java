package UninformedSearch.DLS;

import java.util.*;

public class EightPuzzleProblem {
    private static final int SIZE = 3; // Size of the puzzle board
    private static final int[][] GOAL_STATE = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } }; // Goal state

    public static void main(String[] args) {
        EightPuzzleProblem problem = new EightPuzzleProblem();
        int[][] initialState = { { 1, 2, 3 }, { 0, 4, 6 }, { 7, 5, 8 } }; // Updated initial state

        System.out.println("\nDLS:");
        printResult(problem.dls(initialState, 5), problem.dlsStates);
    }

    static class PuzzleState {
        int[][] board;

        PuzzleState(int[][] board) {
            this.board = board;
        }

        public boolean equals(Object o) {
            if (this == o)
                return true;
            if (o == null || getClass() != o.getClass())
                return false;
            PuzzleState state = (PuzzleState) o;
            return Arrays.deepEquals(board, state.board);
        }

        public int hashCode() {
            return Arrays.deepHashCode(board);
        }
    }

    int dlsStates = 0;

    private List<PuzzleState> getNeighbors(PuzzleState state) {
        List<PuzzleState> neighbors = new ArrayList<>();
        int zeroRow = -1, zeroCol = -1;
        // Find the position of the zero (empty) tile
        outerloop: for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (state.board[i][j] == 0) {
                    zeroRow = i;
                    zeroCol = j;
                    break outerloop;
                }
            }
        }

        // Generate neighbors by moving the zero tile
        int[][] moves = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
        for (int[] move : moves) {
            int newRow = zeroRow + move[0];
            int newCol = zeroCol + move[1];
            if (isValidMove(newRow, newCol)) {
                int[][] newBoard = copyBoard(state.board);
                swap(newBoard, zeroRow, zeroCol, newRow, newCol);
                neighbors.add(new PuzzleState(newBoard));
            }
        }
        return neighbors;
    }

    private boolean isValidMove(int row, int col) {
        return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
    }

    private int[][] copyBoard(int[][] board) {
        int[][] newBoard = new int[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            System.arraycopy(board[i], 0, newBoard[i], 0, SIZE);
        }
        return newBoard;
    }

    private void swap(int[][] board, int row1, int col1, int row2, int col2) {
        int temp = board[row1][col1];
        board[row1][col1] = board[row2][col2];
        board[row2][col2] = temp;
    }

    private List<PuzzleState> constructPath(Map<PuzzleState, PuzzleState> parentMap, PuzzleState goal) {
        List<PuzzleState> path = new ArrayList<>();
        for (PuzzleState at = goal; at != null; at = parentMap.get(at))
            path.add(at);
        Collections.reverse(path);
        return path;
    }

    public List<PuzzleState> dls(int[][] initialState, int limit) {
        return dlsRecursive(new PuzzleState(initialState), new HashSet<>(), new HashMap<>(), limit);
    }

    private List<PuzzleState> dlsRecursive(PuzzleState current, Set<PuzzleState> visited,
            Map<PuzzleState, PuzzleState> parentMap, int limit) {
        dlsStates++;
        if (isGoalState(current))
            return constructPath(parentMap, current);
        if (limit == 0)
            return Collections.emptyList();
        visited.add(current);
        for (PuzzleState neighbor : getNeighbors(current)) {
            if (!visited.contains(neighbor)) {
                parentMap.put(neighbor, current);
                List<PuzzleState> result = dlsRecursive(neighbor, visited, parentMap, limit - 1);
                if (!result.isEmpty())
                    return result;
            }
        }
        visited.remove(current);
        return Collections.emptyList();
    }

    private boolean isGoalState(PuzzleState state) {
        return Arrays.deepEquals(state.board, GOAL_STATE);
    }

    private static void printResult(List<PuzzleState> result, int statesExplored) {
        if (result.isEmpty()) {
            System.out.println("No solution found.");
        } else {
            for (int i = 0; i < result.size(); i++) {
                System.out.println("Step " + i + ":");
                printBoard(result.get(i).board);
            }
            System.out.println("Total states explored: " + statesExplored);
        }
    }

    private static void printBoard(int[][] board) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
}
