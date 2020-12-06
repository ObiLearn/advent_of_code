package extio

import (
	"bufio"
	"fmt"
	"os"
)

func PipeReader() (*bufio.Reader, error) {
	info, err := os.Stdin.Stat()
    if err != nil {
		return nil, err
    }

	if info.Mode()&os.ModeCharDevice != 0 || info.Size() <= 0 {
		return nil, fmt.Errorf("The command is intended to work with pipes.")
	}

	return bufio.NewReader(os.Stdin), nil
}
