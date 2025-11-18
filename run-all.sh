#!/bin/bash

echo "=================================="
echo "  Sorting Algorithm Analysis"
echo "=================================="
echo ""

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}[1/3]${NC} Running sorting algorithm experiments..."
make run

if [ $? -ne 0 ]; then
    echo "Error: Failed to run experiments"
    exit 1
fi

echo ""
echo -e "${GREEN}✓${NC} Experiments complete!"
echo ""

echo -e "${BLUE}[2/3]${NC} Copying results to visualization..."
cd visualization
npm run copy-results
cd ..

echo -e "${GREEN}✓${NC} Results copied!"
echo ""

echo -e "${BLUE}[3/3]${NC} Starting visualization server..."
echo ""
echo "Opening browser at http://localhost:5173"
echo "Press Ctrl+C to stop the server"
echo ""

cd visualization
npm run dev
