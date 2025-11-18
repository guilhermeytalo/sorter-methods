import { useState, useEffect } from 'react'
import {
  LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer
} from 'recharts'
import './App.css'

const COLORS = {
  'Bubble Sort': '#ef4444',
  'Insertion Sort': '#f59e0b',
  'Heap Sort': '#10b981',
  'Merge Sort': '#3b82f6',
  'Quick Sort': '#8b5cf6',
  'Radix Sort': '#ec4899'
}

function App() {
  const [data, setData] = useState(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)
  const [metric, setMetric] = useState('comparisons')
  const [visibleAlgorithms, setVisibleAlgorithms] = useState({
    'Bubble Sort': true,
    'Insertion Sort': true,
    'Heap Sort': true,
    'Merge Sort': true,
    'Quick Sort': true,
    'Radix Sort': true
  })

  useEffect(() => {
    fetch('/results/data.json')
      .then(res => {
        if (!res.ok) throw new Error('Data file not found. Run "make run" first!')
        return res.json()
      })
      .then(jsonData => {
        setData(jsonData)
        setLoading(false)
      })
      .catch(err => {
        setError(err.message)
        setLoading(false)
      })
  }, [])

  const toggleAlgorithm = (algo) => {
    setVisibleAlgorithms(prev => ({ ...prev, [algo]: !prev[algo] }))
  }

  const formatChartData = () => {
    if (!data) return []

    const grouped = {}
    data.results.forEach(result => {
      if (!grouped[result.size]) {
        grouped[result.size] = { size: result.size }
      }
      grouped[result.size][result.algorithm] = result[metric]
    })

    return Object.values(grouped).sort((a, b) => a.size - b.size)
  }

  if (loading) {
    return (
      <div className="container loading">
        <div className="spinner"></div>
        <p>Loading experiment data...</p>
      </div>
    )
  }

  if (error) {
    return (
      <div className="container error">
        <h2>⚠️ Error Loading Data</h2>
        <p>{error}</p>
        <div className="instructions">
          <h3>To generate the data:</h3>
          <ol>
            <li>Open a terminal in the project root</li>
            <li>Run: <code>make run</code></li>
            <li>Wait for the experiment to complete</li>
            <li>Refresh this page</li>
          </ol>
        </div>
      </div>
    )
  }

  const chartData = formatChartData()

  return (
    <div className="container">
      <header>
        <h1>Sorting Algorithm Complexity Analysis</h1>
        <p className="subtitle">
          Empirical comparison of 6 sorting algorithms • {data.metadata.trials} trials per size
        </p>
      </header>

      <div className="controls">
        <div className="metric-selector">
          <label>Metric:</label>
          <div className="buttons">
            <button
              className={metric === 'comparisons' ? 'active' : ''}
              onClick={() => setMetric('comparisons')}
            >
              Comparisons
            </button>
            <button
              className={metric === 'swaps' ? 'active' : ''}
              onClick={() => setMetric('swaps')}
            >
              Swaps
            </button>
          </div>
        </div>

        <div className="algorithm-toggles">
          <label>Algorithms:</label>
          <div className="toggle-grid">
            {Object.entries(visibleAlgorithms).map(([algo, visible]) => (
              <button
                key={algo}
                className={`toggle-btn ${visible ? 'active' : ''}`}
                style={{ '--color': COLORS[algo] }}
                onClick={() => toggleAlgorithm(algo)}
              >
                <span className="indicator"></span>
                {algo}
              </button>
            ))}
          </div>
        </div>
      </div>

      <div className="chart-container">
        <ResponsiveContainer width="100%" height={500}>
          <LineChart data={chartData} margin={{ top: 5, right: 30, left: 20, bottom: 5 }}>
            <CartesianGrid strokeDasharray="3 3" stroke="#374151" />
            <XAxis
              dataKey="size"
              label={{ value: 'Array Size (n)', position: 'insideBottom', offset: -5 }}
              stroke="#9ca3af"
            />
            <YAxis
              label={{ value: metric === 'comparisons' ? 'Comparisons' : 'Swaps', angle: -90, position: 'insideLeft' }}
              stroke="#9ca3af"
            />
            <Tooltip
              contentStyle={{
                backgroundColor: '#1f2937',
                border: '1px solid #374151',
                borderRadius: '8px',
                color: '#f3f4f6'
              }}
            />
            <Legend />
            {Object.entries(visibleAlgorithms).map(([algo, visible]) => (
              visible && (
                <Line
                  key={algo}
                  type="monotone"
                  dataKey={algo}
                  stroke={COLORS[algo]}
                  strokeWidth={2}
                  dot={false}
                  activeDot={{ r: 6 }}
                />
              )
            ))}
          </LineChart>
        </ResponsiveContainer>
      </div>

      <div className="stats">
        <div className="stat-card">
          <div className="stat-label">Total Array Sizes Tested</div>
          <div className="stat-value">{chartData.length}</div>
        </div>
        <div className="stat-card">
          <div className="stat-label">Trials per Size</div>
          <div className="stat-value">{data.metadata.trials}</div>
        </div>
        <div className="stat-card">
          <div className="stat-label">Max Array Size</div>
          <div className="stat-value">{data.metadata.maxSize}</div>
        </div>
      </div>

      <footer>
        <p>University Sorting Algorithm Analysis Project</p>
        <p className="tech-stack">Built with C, React, and Recharts</p>
      </footer>
    </div>
  )
}

export default App
