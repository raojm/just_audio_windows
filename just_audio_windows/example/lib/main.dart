import 'package:flutter/material.dart';

import 'package:just_audio/just_audio.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final AudioPlayer player = AudioPlayer();

  @override
  void initState() {
    super.initState();
    player.setUrl(
      'https://s3.amazonaws.com/scifri-episodes/scifri20181123-episode.mp3',
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: const Center(
          child: Text('THIS IS AN EXAMPLE APP'),
        ),
      ),
    );
  }
}
