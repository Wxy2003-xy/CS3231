import React from 'react';
import { HashRouter as Router, Route, Link, Routes } from 'react-router-dom';
import './App.css';
import MyPdfViewer from './PDFViewer.tsx'

// Components for sub-pages
const Home: React.FC = () => (
  <div>
    <header className="App-header">
      <p>
        Edit <code>src/App.tsx</code> and save to reload.
      </p>
      <Link to="/about" className="App-link">
        Go to About Page
      </Link>
    </header>
  </div>
);

const About: React.FC = () => (
  <div>
    <header className="App-header">
      <h1>About Page</h1>
      <Link to="/" className="App-link">
        Go to Home Page
      </Link>
    </header>
  </div>
);

function App() {
  return (
    <>
    <h1>CS3231 Notes by Wxy2003-xy</h1>
    <MyPdfViewer filePath="../../Week1/DFAtoLang.pdf" />
    <Router>
      <Routes>
        <Route path="/" element={<Home/>} />
        <Route path="/about" element={<About/>} />
      </Routes>
    </Router>
    </>
  );
}

export default App;
