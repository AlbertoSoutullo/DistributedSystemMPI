

int recv_ID()
{
    int id = -1;
    MPI_Comm parent;
    MPI_Status status;
    MPI_Comm_get_parent(&parent);

    MPI_Recv(&id, 1, MPI_INT, 0, MPI_ANY_TAG, parent, &status);
    return id;
}


int main(int argc, char** argv)
{
    int rank = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

}
