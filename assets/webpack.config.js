const { join } = require('path');

// PLUGINS
// =======

const CopyWebpackPlugin = require('copy-webpack-plugin');
const ExtractTextPlugin = require('extract-text-webpack-plugin');

// PATHS
// =====

const PATHS = {
  src: join(__dirname, 'src'),
  static: join(__dirname, 'static'),
  css: join(__dirname, 'css'),
  build: join(__dirname, '../priv/static'),
}

// CONFIG
// ======

module.exports = {
  entry: [
    join(PATHS.src, 'app.re'),
  ],
  output: {
    path: PATHS.build,
    pathinfo: true,
    filename: 'js/app.js',
    chunkFilename: 'js/[name].chunk.js',
  },
  module: {
    rules: [
      {
        exclude: [
          /\.re$/,
          /\.rei$/,
          /\.ml$/,
          /\.mli$/,
          /\.css$/,
          /\.js$/,
        ],
        include: PATHS.static,
        loader: require.resolve('file-loader'),
      },
      {
        test: /\.(re|rei|ml|mli)$/,
        loader: require.resolve('bs-loader'),
      },
      {
        test: /\.css$/,
        loader: ExtractTextPlugin.extract({
          fallback: require.resolve('style-loader'),
          use: require.resolve('css-loader'),
        }),
      },
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader',
        query: {
          preset: ['es2015'],
        },
      },
      {
        test: /\.(png|woff|woff2|eot|ttf|svg)$/,
        loader: 'url-loader?limit=100000',
      },
    ],
  },
  resolve: {
    extensions: ['.re', '.rei', '.ml', '.mli', '.js'],
    alias: {
      css: PATHS.css,
    },
  },
  plugins: [
    new ExtractTextPlugin('css/app.css'),
    new CopyWebpackPlugin([
      { from: join(PATHS.static) },
    ]),
  ],
};
