const { join } = require('path');

module.exports = {
  entry: join(__dirname, 'src/app.re'),
  output: {
    filename: 'app.js',
    path: join(__dirname, '../priv/static/js'),
  },
  module: {
    rules: [
      {
        test: /\.(re|rei|ml|mli)$/,
        use: 'bs-loader',
      },
    ],
  },
  resolve: {
    extensions: ['.re', '.rei', '.ml', '.mli', '.js'],
  },
};
