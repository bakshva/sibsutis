int sc_commandValidate(int command)
{
    command = (unsigned int)command;
    if (command < 0 || command > 128) {
        return -1;
    }
    return 0;
}